#!/usr/local/bin/python3

import subprocess
import os, shutil
import json
import psutil
import time
import numpy as np
from enum import Enum
import contexttimer

POLL_RATE_S = 0.1
HERE = os.path.abspath(os.path.dirname(__file__))
MAPS_DIR = 'maps'
REPOS_DIR = 'repos'
OUTPUT_DIR = 'output'


class BSQEntry(object):
	def __init__(self, identifier:str, git_url:str, makefile_dir:str, **kwargs):
		self.identifier = identifier
		self.git_url = git_url
		self.makefile_dir = makefile_dir
		self.__dict__.update(**kwargs)

	def clone(self):
		if not os.path.isdir(self.repository_root_path):
			subprocess.check_call(['git', 'clone', self.git_url, self.repository_root_path])
		else:
			print(f"Not cloning because dir {self.identifier} already exists")

	def build(self):
		os.chdir(HERE)
		os.chdir(self.bsq_makefile_dir)
		print(f"building {self.git_url}")
		try:
			subprocess.check_call(['make'])
		except subprocess.CalledProcessError as e:
			print(f"failed to build with error {e}")
			self.is_buildable = False
		os.chdir(HERE)

	@property
	def repository_root_path(self):
		return os.path.join(HERE, REPOS_DIR, self.identifier)

	@property
	def bsq_makefile_dir(self):
		return os.path.join(self.repository_root_path, self.makefile_dir)

	@property
	def is_buildable(self):
		return False if self.__dict__.get('do_not_use') else True

	@property
	def binary_path(self):
		return os.path.relpath(os.path.join(self.bsq_makefile_dir, "bsq"), HERE)


class RepositoryManager(object):
	def __init__(self, repo_json_filename: str):
		self.repo_json = self.load(repo_json_filename)
		self.filename = repo_json_filename
		self.entries = [BSQEntry(**kwargs) for kwargs in self.repo_json]
	
	def load(self, filename: str) -> dict:
		with open(filename, "r") as repofile:
			repos = json.load(repofile)
			for repo in repos:
				if not repo.get('identifier'):
					repo['identifier'] = next((str(n) for n in range(len(repos)) if str(n) not in [r.get("identifier") for r in repos]))
					print(f"Assigned ID {repo['identifier']} to repo: {repo['git']}")
			return repos

	def	save(self, filename: str=None) -> None:
		""" save the id of the repo to the json file such that it persists. """
		with open(filename or self.filename, "w") as repofile:
			json.dump(self.repo_json, repofile, sort_keys=True, indent=4)

	@property
	def buildable_entries(self):
		return [e for e in self.entries if e.is_buildable]

class BSQMap(object):
	def __init__(self, x: int, y: int, density: int):
		"""
		:int density: [0 - 100]% obstacle density probability.  0 is no chance of obstacles.  100 means obstacles always.

		our friend `gen_map.pl` considers obstacle density [0-100]% to be scaled to the range [0-2*y].
		Fortunately, it takes decimal numbers.
		"""
		self.x = x
		self.y = y
		self.density = (float(density) / 100) * 2 * y
		if not os.path.isdir(MAPS_DIR):
			os.mkdir(MAPS_DIR)
		self._basename = f"map_{x}_{y}_{density}"
		self.path = f"{MAPS_DIR}/{self._basename}"
		with open(self.path, "w") as outfile:
			subprocess.check_call(["perl", "../gen_map.pl", 
			str(x), str(y), str(self.density)], stdout=outfile)

	def __str__(self):
		return self.path

	@staticmethod
	def all_maps():
		return os.listdir(MAPS_DIR)

	@staticmethod
	def remove_all():
		for f in os.listdir(MAPS_DIR):
			fp = os.path.join(MAPS_DIR, f)
			os.unlink(fp)

# 
#  Profiling Functions
# 

BSQInputMethod = Enum('BSQInputMethod', 'STDIN FILENAME')

RUNTIME_AVERAGER_SET_SIZE = 5 
def profile_bsq_runtime(path_to_binary: str, mapfile: str, outfile:str, input_as=BSQInputMethod.STDIN):
	""" run a few times to collect an average and a variance """
	runtimes = []
	mapfile = f"{MAPS_DIR}/{mapfile}"
	print(f'\t{input_as: <{14}}', end='\t')
	for run in range(RUNTIME_AVERAGER_SET_SIZE):
		cmd = [f"./{path_to_binary}", mapfile]
		outfile_fullname = f"{outfile}_{input_as}"
		try:
			with open(outfile_fullname, 'w') as ofile:
				with contexttimer.Timer() as t:
					if BSQInputMethod.STDIN:
						bsq = subprocess.check_call(cmd, stdout=ofile)
					elif BSQInputMethod.FILENAME:
						with open(mapfile, 'r') as the_map:
							bsq = subprocess.check_call(cmd, stdin=mapfile, stdout=ofile)
				runtimes.append(t.elapsed)		
		except subprocess.CalledProcessError as e:
			print(f"failed to run {path_to_binary} with exception {e}")
	with open(outfile_fullname, 'r') as ofile:
		if "map error" in ofile.read():
			print("Failed with map error")
			return -1, -1
		else:
			avg = sum(runtimes) / RUNTIME_AVERAGER_SET_SIZE
			variance = np.var(runtimes)
			print(f"Avg: {avg:.3f}s\t variance: {variance:.3f}s")
			return avg, variance

def profile_bsq_memory_usage(path_to_binary: str, mapfile: str, outfile: str, input_as=BSQInputMethod.STDIN):
	"""
	memory usage is a little hard to capture because varies over the duration of program execution.
	"""

def kill_all_bsq():
	try:
		subprocess.call(['killall', 'bsq'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
	except subprocess.CalledProcessError:
		pass

def purge_output_dir():
	if not os.path.isdir(OUTPUT_DIR):
		os.mkdir(OUTPUT_DIR)
	for f in os.listdir(OUTPUT_DIR):
		fp = os.path.join(OUTPUT_DIR, f)
		os.unlink(fp)
	


def main() -> None:
	repo_man = RepositoryManager('repos.json')
	[entry.clone() for entry in repo_man.entries]
	[entry.build() for entry in repo_man.entries]
	repo_man.save()

	BSQMap.remove_all()
	BSQMap(x=1, y=1000000, density=50)
	BSQMap(x=1000000, y=1, density=50)
	BSQMap(x=100, y=10000, density=0)
	BSQMap(x=100, y=10000, density=100)
	BSQMap(x=100, y=10000, density=50)

	purge_output_dir()

	# These two are pretty blazing fast.
	selected_entries = [e for e in repo_man.buildable_entries if e.identifier in ['2', '9', '14']]

	for entry in selected_entries:
		print(f">>>>> repo: {entry.git_url}  I'll average {RUNTIME_AVERAGER_SET_SIZE} runs.")
		for mapfile in BSQMap.all_maps():
			outfile = os.path.join(OUTPUT_DIR, f"{entry.identifier}_{os.path.basename(mapfile)}")
			print(f"{mapfile}")
			profile_bsq_runtime(entry.binary_path, mapfile, outfile, BSQInputMethod.STDIN)
			profile_bsq_runtime(entry.binary_path, mapfile, outfile, BSQInputMethod.FILENAME)
		kill_all_bsq()
		

		# profile_bsq_memory_usage(entry.binary_path, )
		# kill_all_bsq()

if __name__ == '__main__':
	main()
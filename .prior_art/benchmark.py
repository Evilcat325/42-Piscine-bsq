#!/usr/local/bin/python3

import subprocess
import os, shutil
import json
import psutil
import time
import numpy as np
import contexttimer

POLL_RATE_S = 0.1
CUR_DIR = os.getcwd()
MAPS_DIR = 'maps'

class RepositoryTyrant(object):
	def __init__(self, repo_json_filename: str):
		self.repos = self.load(repo_json_filename)
		self.filename = repo_json_filename
	
	@property
	def buildable_repos(self):
		return [repo for repo in self.repos if not repo.get('do_not_use')]

	def load(self, filename: str) -> dict:
		with open(filename, "r") as repofile:
			repos = json.load(repofile)
			for repo in repos:
				if not repo.get("id"):
					repo['id'] = next((str(n) for n in range(len(repos)) if str(n) not in [r.get("id") for r in repos]))
					print(f"Assigned ID {repo['id']} to repo: {repo['git']}")
			return repos

	def	save(self, filename: str=None) -> None:
		""" save the id of the repo to the json file such that it persists. """
		with open(filename or self.filename, "w") as repofile:
			json.dump(self.repos, repofile, sort_keys=True, indent=4)

	def clone_all(self) -> None:
		for repo in self.repos:
			if not os.path.isdir(repo['id']):
				subprocess.check_call(['git', 'clone', repo["git"], repo['id']])
			else:
				print(f"Not cloning because dir {repo['id']} exists")

	def build_bsq_binaries(self) -> None:
		for repo in self.buildable_repos:
			rel_path = os.path.join(repo['id'], repo['dir'])
			print(f"entering dir {rel_path}")
			os.chdir(rel_path)
			print(subprocess.check_call(['make', 're']))
			os.chdir(CUR_DIR)


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
			str(x), str(y), str(density)], stdout=outfile)

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

def profile_bsq_with_args(path_to_binary: str, mapfile: str, log_name: str, plot_name: str):
	cmd = [f"./{path_to_binary}", f"{MAPS_DIR}/{mapfile}"]
	print(f"Starting up command '{cmd}' and attaching to process")
	sprocess = subprocess.Popen(cmd)
	pid = sprocess.pid

def profile_bsq_with_stdin():
	raise NotImplementedError

RUNTIME_AVERAGER_SET_SIZE = 5
def profile_bsq_runtime(path_to_binary: str, mapfile: str):
	""" run a few times to collect an average and a variance """
	runtimes = []
	for run in range(RUNTIME_AVERAGER_SET_SIZE):
		with open(f"os.path.basename(path_to_binary)_output.txt", 'w') as outfile:
			with contexttimer.Timer() as t:
				cmd = [f"./{path_to_binary}", f"{MAPS_DIR}/{mapfile}"]
				bsq = subprocess.check_call(cmd, stdout=outfile)
			runtimes.append(t.elapsed)
	avg = sum(runtimes) / RUNTIME_AVERAGER_SET_SIZE
	variance = np.var(runtimes)
	print(f"Avg: {avg:.3f}s\t variance: {variance:.3f}s")

def print_output_from_bsqs(path_to_binary: str, mapfile: str):
	try:
		cmd = [f"./{path_to_binary}", f"{MAPS_DIR}/{mapfile}"]
		bsq = subprocess.Popen(cmd, stdout=subprocess.PIPE)
		bsq_process = psutil.Process(pid=bsq.pid)
		import ipdb; ipdb.set_trace()
		stdout_data = bsq.communicate()[0]
		if stdout_data:
			print(stdout_data.decode('ascii'))
		else:
			print(f'No output from {path_to_binary}')
	except Exception as e:
		print(f"Failed to execute {path_to_binary} with error {e}")

def kill_all_bsq():
	try:
		subprocess.call(['killall', 'bsq'], stdout=None, stderr=None)
	except subprocess.CalledProcessError:
		pass

def main() -> None:
	repo_man = RepositoryTyrant('repos.json')
	# repo_man.clone_all()
	# repo_man.build_bsq_binaries()
	repo_man.save()

	BSQMap.remove_all()
	BSQMap(x=1, y=100000, density=50)
	BSQMap(x=100000, y=1, density=50)
	BSQMap(x=100, y=1000, density=0)
	BSQMap(x=100, y=1000, density=100)
	BSQMap(x=100, y=1000, density=50)

	for repo in repo_man.repos:
		print(f"repo: {repo['git']}  Averaging {RUNTIME_AVERAGER_SET_SIZE} runs.")
		for mapfile in BSQMap.all_maps():
			print(f"map: {mapfile}", end='\t')
			binary = os.path.join(repo["id"], repo["dir"], "bsq")
			profile_bsq_runtime(binary, mapfile)
		kill_all_bsq()
	"""
	- benchmark solve time and memory usage for the following cases
	--> all empty
	--> all full
	--> single horizontal
	--> single vertical

	--> generate a few random boards
	"""

if __name__ == '__main__':
	main()
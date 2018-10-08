#!/usr/local/bin/python3

import subprocess
import os, shutil
import json
from psrecord import monitor

CUR_DIR = os.getcwd()
MAPS_DIR = 'maps'

def load_repos(filename: str) -> dict:
	with open(filename) as repofile:
		repos = json.load(repofile)
		for num, repo in enumerate(repos):
			repo["id"] = str(num)
		return repos

def clone_repos(repos: dict) -> None:
	for repo in repos:
		if not os.path.isdir(repo['id']):
			subprocess.check_call(['git', 'clone', repo["git"], repo['id']])
		else:
			print(f"dir {repo['id']} exists")

def build_bsqs(repos: dict) -> None:
	for repo in repos:
		rel_path = os.path.join(repo['id'], repo['dir'])
		print(f"entering dir {rel_path}")
		os.chdir(rel_path)
		print(subprocess.check_call(['make']))
		os.chdir(CUR_DIR)

def generate_maps(x, y, rho, num_maps):
	if not os.path.isdir(MAPS_DIR):
		os.mkdir(MAPS_DIR)
	for i in range(num_maps):
		map_name = f"map_{i}_{x}_{y}_{rho}"
		with open(f"maps/{map_name}", "w") as outfile:
			subprocess.check_call(["perl", "../gen_map.pl", 
			str(x), str(y), str(rho)], stdout=outfile)

def remove_maps():
	for f in os.listdir(MAPS_DIR):
		fp = os.path.join(MAPS_DIR, f)
		os.unlink(fp)

def profile_bsq_with_args(path_to_binary: str, mapfile: str, log_name: str, plot_name: str):
	cmd = [f"./{path_to_binary}", f"{MAPS_DIR}/{mapfile}"]
	print(f"Starting up command '{cmd}' and attaching to process")
	sprocess = subprocess.Popen(cmd)
	pid = sprocess.pid
	monitor(pid, logfile=log_name, plot=plot_name, duration=5, interval=0.01)

def profile_bsq_with_stdin():
	raise NotImplementedError


def print_output_from_bsqs(path_to_binary: str, mapfile: str):
	try:
		cmd = [f"./{path_to_binary}", f"{MAPS_DIR}/{mapfile}"]
		bsq_process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
		stdout_data = bsq_process.communicate()[0]
		if stdout_data:
			print(stdout_data.decode('ascii'))
		else:
			print(f'No output from {path_to_binary}')
	except Exception as e:
		print(f"Failed to execute {path_to_binary} with error {e}")



def main() -> None:
	# remove_maps()
	# generate_maps(x=40, y=40, rho=3, num_maps=20)
	repos = load_repos('repos.json')
	# clone_repos(repos)
	# build_bsqs(repos)

	mapfile = next((f for f in os.listdir(MAPS_DIR)))
	for repo in repos:
		binary = os.path.join(repo["id"], repo["dir"], "bsq")
		logname = "{}.log".format(repo["id"])
		plotname = "{}.png".format(repo["id"])
		# profile_bsq_with_args(binary, mapfile, logname, plotname)
		print_output_from_bsqs(binary, mapfile)

if __name__ == '__main__':
	main()
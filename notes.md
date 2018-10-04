# Problem

find biggest square, avoiding obstacles.
if more than one soln, choose the most top-left square.

# File header format
- nlines
- empty char
- obstacle char
- full char

# Scoring
10 points for meeting functional requirements
5 points for execution speed
5 points for memory usage

# Required Components

## Makefile

## Auteur file

## Parser

### Types of inputs
- [1-n] filenames as args
- if no args, read (?one?) board from stdin

### Validation
- all lines are same length
- there's at least one line
- there's at least one line that contains a box
- all char types exist in the set [empty, obstacle, full]

#### If invalid
  - display `"map error\n"`
  - consume the next map
  

## Todo:

build and profile all available existing solvers
- norms?
- builds?
- memory usage?  
  - https://psutil.readthedocs.io/en/release-3.4.2/#psutil.Process.memory_info
- execution speed?
  - timeit

https://github.com/MrRobb/42_piscine/tree/master/BSQ
https://github.com/fwuensche/42-piscine-c/tree/master/bsq
https://github.com/Tolo789/BSQ
https://github.com/vmarchaud/42-piscine/tree/master/bsq
https://github.com/hopeczuba/bsq
https://github.com/SuperSpyTX/42-Piscine/tree/master/bsq
https://gitlab.pelt10.fr/Piroli/42-piscine-C/tree/36749f1dae49a14866c2ead2f9b8c628a2bd91b3/BSQ
https://github.com/alvinsunyixiao/42-piscine/tree/master/bsq
https://github.com/Zevran/BSQ
https://github.com/jraleman/42_Piscine-C/tree/master/bsq
https://github.com/malikbenkirane/42.pc.bsq
https://github.com/EvaldoNeto/BSQ
https://github.com/Hoax017/-42-BSQ


## Solver

hypothesis -- we want to store memory on the stack


# What takes long?

Approximate timing for various operations on a typical PC:

(http://norvig.com/21-days.html)

| execute typical instruction | 1/1,000,000,000 sec = | 1 nanosec | 
|-|-|-|
| fetch from L1 cache memory | 	| 0.5 nanosec | 
| branch misprediction | | 5 nanosec | 
| fetch from L2 cache memory | |	7 nanosec | 
| Mutex lock/unlock	| | 25 nanosec | 
| fetch from main memory | |	100 nanosec | 
| send 2K bytes over 1Gbps network | |	20,000 nanosec | 
| read 1MB sequentially from memory	| | 250,000 nanosec | 
| fetch from new disk location (seek) | |	8,000,000 nanosec | 
| read 1MB sequentially from disk | |	20,000,000 nanosec | 
| send packet US to Europe and back	| 150 milliseconds = | 150,000,000 nanosec 


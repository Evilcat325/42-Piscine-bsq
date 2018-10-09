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


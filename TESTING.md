# Sudoku Testing

# Bash Testing Overview

The folder contains a bash file `testing.sh`. The file can be run using `make test`to print the result the stdout or `make test &> testing.out` to redirect the output to a `testing.out` file. The output tests for both invalid and valid cases.

## Inavlid cases:

The testing file tests for invalid number of arguments, invalid mode, invalid directory.

## Valid cases: 

Valid testing is run on  `create` in `easy` and `hard` as well as solve takes the output of these creations

# Fuzz Testing

**./fuzztesting difficulty numSudoku**

Fuzz testing creates a set number of puzzles, verifying that each puzzle follows Sudoku rules, is solvable, and has a unique solution

Note: fuzz testing does not check for valid arguements as it is assumed the user is aware of its useage and limitations

# Run Time:

We tested out our fuzz testing, building and solving a range of sudoku boards (3-20) with both difficulties (easy and hard) and found the average time fell un the following ranges:

Easy: 0.0003-0.0004 seconds
Hard: 0.1-0.4 seconds 

# Unit Testing

Unit testing was done on various methods in the puzzle.c module. This file includes, but is not limited to, testing on creating a puzzle, setting values, getting values, and checking if a value is in a point's cross sections. This can be run by running `make unittesting` after the program is compiled, which then runs the `unittesting.sh` script. The `unittesting.sh` script outputs to `unittesting.out`, a .out file separate from `testing.out`, which contains the output of the integration and fuzz testing, not unit testing. The compiled file is in the larger `project-sudoku-team5` directory.

# Sudoku Visual Testing

Despite the large number of tests performed above, much of our initial testing was visual. This meant building full sudokus and checking if they followed the rules. We also had our remove method remove points and then re-solve it, ensuring the solved sudoku is valid and is the same as the original sudoku created.
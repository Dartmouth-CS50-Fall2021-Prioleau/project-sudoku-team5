# Sudoku Testing

# Bash Testing Overview

The folder contains a bash file `testing.sh`. The file can be run using `make test`to print the result the stdout or `make test &> testing.out` to redirect the output to a `testing.out` file. The output tests for both invalid and valid cases.

## Inavlid cases:

The testing file tests for invalid number of arguments, invalid mode, invalid directory.

## Valid cases: 

Valid testing is run on  `create` in `easy` and `hard` as well as solve takes the output of these creations

# Fuzz Testing

Fuzz testing creates a set number of puzzles, verifying that each puzzlie follows Sudoku rules, is solvable, and has a unique solution

# Unit Testing

Unit testing was done on various methods in the puzzle.c a file. This file includes, but is not limited to, testing on creating a puzzle, setting values, getting values, and checking a value uf a value is in a point's cross sections. This can be run by uncommenting the `#-DUNIT_TEST` flag, running `make unittest` followed by `make unit`. 

# Sudoku Visual Testing

Despite the large number of tests preformed above, much of our initial testing was visual. This meant building full sudokus and checking if they followed the rules. We also had our remove method remove points and then re-solve it, ensuring the solved sudoku is valid and is the same as the original sudoku created.
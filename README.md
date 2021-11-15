# Team 5
## Dylan Bienstock, Salifyanji J Namwila, Veronica Quidore
## CS50 Fall 2021, Final Project - Sudoku 2.0

GitHub usernames: dylanbien, vquidore, Sheinstein

# Sudoku

The Sudoku is a standalone program to create and solve Sudoku puzzles according to bewlow rules.

Rules:
* In a valid Sudoku grid, every number from 1 to 9 must appear:
    * Only once in every row
    * Only once in every column
    * Only once in every 3x3 squared region

# Functionality

Our Sudoku meets the full specs. It is able to create a unique sudoku board in both easy and hard. It also also able to solve a given sudoku, identifying if the given board is not solvable.

# Topping

Our topping is the optional argument of the sudoku board size. It is able to handle any sized sudoku board, checking that this new input is a perfect square

# Support

For this lab we used the support of the learning fellows during lab time. We also used the cs50 library files, lecture notes, lecture examples, activites, and activities solutions.

# Usage

**./sudoku mode difficulty**

A valid command line has:
* mode in {create, solve}
* difficulty in {easy, hard}

Note: In mode = `solve`, the difficulty argument is optionanl

# Safety
1. Whenever we allocated memory, we called `assertp`. This checks if the pointer is null, and if so, prints an error and exits the code. While we recogize the does not free previously allocated memory, it is better to quit on an error than continue 

# Files

* `.gitignore` - specifies intentionally untracked files that Git should ignore
* `Makefile` - compilation procedure
* `sudoku.c` - the implementation for sudoku
* `./library/` - a folder containing support modules for sudoku provided by the course
* `./puzzle/` - a folder containing the puzzle struct and related methods to create, update, access, and print it
* `./create/` - a folder containing modules used when creating and a sudoku
* `./solve/` - a folder containing modules used when solving and a sudoku
* `./common/` - a folder containing modules used in both creating and solving a sudoku
* `IMPLEMENTATION.md` - a file to describe the implementation of the sudoku program 
* `DESIGN.md` - a file to describe the design of the sudoku program
* `TESTING.md` -  a file to describe the testing of the sudoku program
* `testing.sh` - a bash script run by `make test` to test the sudoku program
* `testing.out` - result of `make test &> testing.out`
* `unittesting.sh`  - a bash script run by `make unittesting` to test the sudoku program
* `unittesting.out` - result of `make unittesting &> unittesting.out`

# GIT

In order to maximize our efficiency and workflow, we regularly pushed our individual work to Github at least once every day and opened up and reviewed each others's pull requests to merge codde updates into our main branch accordingly. 

We did, however, run into some difficulties with merging, and several times had to copy our code onto new branches to more seamlessly pull code from or merge into the main branch. 

Because of this, there are 9 branches for 3 group members. 

We also leveraged our close proximity in person to meet almost daily and discuss our changes and progress. 

Together, we resolved our merge conflicts and avoided any losses of code. 

# Compilation

To compile, simply `make`.

# Implementation

See Implementation.md

# Commentary

## recursion/backtracking

The `sudoku` program uses recursion and backtracking to output both created and solved puzzles. On each coordinate in the grid, the program calls the `solve sudoku` method, which seeks a solvable solution and recurses until one is found (boolean returns `true`). It backtracks when an non-unique sudoku is created until the puzzle can be solved at a prior square.

## uniqueness... a diagonal approach

At each coordinate, the program determines if it can reach more than one solution by checking the row, column, sub-box, and sub-box's diagonals for multiple solutions. If other value besides the value about to be deleted cannot result in a valid solution in the diagonals in the sub-box, the solution must be inherently unique. If multiple solutions can be reached, the program picks another random location to try and delete the value until only one solution can be reached with the correct number of values deleted. 

# Testing

See TESTING.md 

# WARNING: Segfault

The 4x4 sudoku intermittently segfaults (at create.c:87 and 86) which traces back to rand.c:27() (error is `random.c: No such file or directory`)and puzzle.c:190, which traces back to puzzle.c:120 (error is `Cannot access memory at location...`). 

We believe this bug to be the result of the `rand()` function. 
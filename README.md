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
* `IMPLEMENTATION.md` - a file to describe the implementation of my querier 
* `DESIGN.md` - a file to describe the design of my querier
* `TESTING.md` -  a file to describe the testing of my querier
* `testing.sh` - a bash script run by `make test` to test my querier
* `testing.out` - result of `make test &> testing.out`

# Compilation

To compile, simply `make`.

# Implementation

See Implementation.md

# Testing

See Testing.md 
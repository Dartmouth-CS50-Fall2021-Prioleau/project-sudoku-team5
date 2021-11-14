# SUDOKU PROJECT
## DESIGN SPEC

### User Interface

Interactions with the sudoku program shall happen on the command line as follows:

$ ./sudoku mode difficulty [size]

In which `mode` is set to `create` or `solve`

`difficulty` is set to `easy` (36 boxes already filled) or `hard` (25 boxes already filled).

and `size` is the number of boxes comprising of a side of one sudoku square (0 < size < 100).

### Inputs and Outputs

#### inputs 

As per the User Interface, the only inputs are those from the commandline and `stdin` (sudoku puzzle to solve for `solve` mode).

#### outputs

If in `create` mode, if the `size` is 9, a valid, formatted sudoku puzzle to be solved with either 37 (`easy`) or 25 (`hard`) boxes assigned a random value of [1,9] printed to `stdout`.
  - If the `size` is a different number, the number of items deleted is determined by a 

If in `solve` mode, a formatted sudoku puzzle fully and correctly solved printed to `stdout`.


### Functional Decomposition Into Modules

1. `sudoku`, which parses arguments, determines the difficulty level, and calls either create mode or solve mode.
2. `create`, which builds a valid sudoku game and prints out the product. 
3. `solve`, which, given a valid sudoku game, solves the game and prints out the filled grid.


### Pseudo code for logic/algorithmic flow

The `sudoku` module shall execute as follows:

1. Determine if the arguments are the correct number and valid.
2. Call the correct mode (and difficulty if the mode is `create`) (`size` is optional).
3. Initialize a sudoku `puzzle` grid of a given SIZE.
4. Print the created or solved sudoku puzzle in the proper format.

The `create` mode shall execute as follows:

1. Normalize the inputted difficulty level. If the level corresponds to 'easy', set the values of 37 boxes. If the level corresponds to 'hard', set the values of 25 boxes. 
2. Pick a random x and y coordinate for a box, each of [0, SIZE).
3. If the box at the given coordinate has a non-zero value [1-9] already, pick a different random box coordinate pair until the current value is 0. Otherwise:
  1. Pick a random value [1,9]. 
  2. If the value is in the box's row, column, or 3x3 box, pick a different random value. Otherwise, set the box's value to the random value.
  3. Update the possible values for the box and in the box's row, column, and 3x3 box.
4. Repeat steps 1-3 until the correct number of boxes (37 or 25) have been assigned a value [1-9] according to the given `easy` or `hard` difficulty. 

The `solve` mode shall execute as follows:

1.	Given a valid, unsolved sudoku
2.	Go through each element struct until you find one whose value is not set (0) and has only only possible solution (only 1 key in the counter has a count 1)
3.	Set the value to for that element to the possible solution 
4.	Update the horizontal, vertical, and boxed elements counter so they can’t include the value as a possibility anymore
5.	Repeat steps 2 through 4 until every value is set
6.	Wrinkle: after updating a value consider looking at the horizonal/vertical/box elements before restarting 

### Dataflow through modules

1. `sudoku` receives arguments from the command line and passes them to one of two modes, `create` or `solve`. It then outputs a  sudoku puzzle (2-D array of boxes) and a formatted printed puzzle. 
2. `create` receives an initialized sudoku and the level needed to build it. It produces a valid sudoku puzzle ready to be solved of level easy or hard.
3. `solve` receives a valid sudoku puzzle from `stdin`. It produces a solved version of that puzzle.

### Major data structures

1. `box_t` holds the [1,9] integer `value` of the box, the box's integer x and y coordinates *(x,y)* on a [0,8] square grid, and a counterset of possible values (key) and possibility count (1 is possible, 0 is impossible) all initialized to 1. 
2. `counters_t` a counterset of possible values for a box (keys) with their status initialized to 1 (possible) and set to 0 if impossible (impossible)

### Testing plan

We will begin with **visual testing** from the `sudoku` main method. We will proceed to conduct **unit testing** on individual methods and modules, **fuzz testing**, and **integration testing**.
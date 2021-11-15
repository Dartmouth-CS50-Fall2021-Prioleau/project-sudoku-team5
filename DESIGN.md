# Dylan Bienstock, Salifyanji J Namwila, Veronica Quidore
## CS-50  `Sudoku` Project 

### User Interface
The indexer's only interface with the user is on the command-line;

#### `create` default mode 

It must always receive two arguments.

```
./sudoku mode difficulty
```
For Example:
 
```
./sudoku create easy 
```

#### `create` optional mode 

It must always receive three arguments.

```
./sudoku mode difficulty size
```
For Example:
 
```
./sudoku create easy  16
```

#### `solve` mode


```
./sudoku mode size 
```
For Example:
 
```
./sudoku solve 16
```

#### `solve` optional difficulty 

It must always receive three arguments.

```
./sudoku mode difficulty  size
```
For Example:
 
```
./sudoku create easy  16
```

### 


#### Sudoku Inputs 

Input: As per the User Interface, the only inputs are those from the commandline and `stdin` (sudoku puzzle to solve for `solve` mode).

#### Sudoku Outputs

`create` mode
Sudoku generates a new board of size 9x9 if the user does not specify size (n) , otherwise generates and nxn zero initialized sudoku. The newly generated sudoku is parsed to build sudoku, which fully builds a unique sudoku by calling solve sudoku in it. NOTE: As long as a sudoku with atleast 17 entries already filly for a 9x9 and at least 20% for larger sized sudoku, we are guaranteed to generate a sudoku with uniqwue solutions. Finally, the fully built sudoku is parsed to create sudoku, which creates the puzzle by selectively deleting a given number of entries to deleted based on the difficulty level.
Sudoku prints a sudoku puzzle which has a guaranteed unique solution to stdout.

`solve` mode

Sudoku reads a puzzle to solve from stdout, assuming that the parsed puzzle has unique solution. It then callse `solve_sudoku` on the parsed sudoku and prints the sodoku to `stdout` formated exactly as was parsed by user. 


### Functional Decomposition Into Modules

1. `sudoku`, which parses arguments, determines the difficulty level, and calls either create mode or solve mode.
2. `create`, which builds a valid sudoku game and and generates a puzzle by deleting a given number of entries based on the difficulty.

3. `solve`, which, given a valid with atleast the minimum number of entries required to guarantee a unique solution, solves the puzzle. Main prints out the sudoku if it was solved, and prints an appropriate could not solve message to user.

### Pseudo code for logic/algorithmic flow through major Functions

#### Sudoku

A. `main` 
1. Parse arguments and creates or solves a sudoku puzzle

#### Create

A.`build full sudoku`

1. Inititiate all the int values in the grid in the parsed empty puzzle to 0.
2. Fill the n nxn mini squares of the n size puzzle in the major diagonals easily by simple checking whether a value to be placed in that box already exists.The underlying idea is that the nXn minisquares do not break the sudoku rules as they are independent of each other.
    1. To accomplish step 2, loop through through the start of these three independent diagonals - locations 0, 1 * sqrt(n), 2 * sqrt(n) 3 * sqrt(n)  ....
        For each diagonal, loop through the nxn rows and columns.
            1. Do:
                 1. Pick  a random number in the range [1,n] inclusive
                 2. Do, while the picked random number is in its repective diagonal.
            2. When a random number  is not in the mini diagnal square, put the number in the square box.
    2. Fill the remainder of the sudoku using recursive backtracking. each time checking if a value is valid in the row, column, and  sqrt(n)x sqrt(n) square.

Output: Fully built sudoku (inplace building)

B. `create sudoku`

1. Loop through the  fully built, `k` times, where K is the deisred number of deltions to make if the fully built sudoku.

    1.Do:
        1. Pick a random location on the grid.
        2. Do while the  value picked location has already been  deleted.
        3. Rememeber that value in a variable.
        4. Loop through  all values from 1 to n to try and find alternative solutions.
            1. Check if the value is valid in on that location.
            2. Put it at that location in the grid
            3. Try to solve the sudoku to check if a valid solution is produced using a value other than stored value.
            4. If the solution is not unique:
                1. Put back the original value i.e the one remembered in a variable.
                2. Select another random location  whose value to delete.
        5. If non of the tried values found alternative valid solutions, the value uniquely produced the solution.
    2. Do while the the solution is not unique.
    3.  If we get, here, its safe to delete. Leave a 0 there.

Output: Puzzle with `k` deleted values, whose solution is unique to the full sudoku solution (inplace building)

#### Solve

A. `solve sudoku`

1. If solve_sudoku is called on a starting location outside the grid, all squares have already been visited. Return true.
2. Loop through all boxes in the grid starting at the given location left to right top to bottom, for each box do the following:
    1. Check if value of that box is empty.
        1. Loop through  every value from 1 to n
            1. if the value is valid in this box
                1. Call `solve sudoku ` on the next box.
                2. If `solve sudoku ` returns true, return true to caller
                3. Otherwise, reset that box to empty.
        2. If we get here, all tired values could not find a solution. Return false to caller.
3. Return true.

Output: Boolean-> true if solution found, false otherwise.

### Dataflow through modules

1. `sudoku` receives arguments from the command line and passes them to one of two modes, `create` or `solve`. It then outputs a  sudoku puzzle (2-D array of boxes) and a formatted printed puzzle. 
2. `create` receives an initialized sudoku and the level needed to build it. It produces a valid sudoku puzzle ready to be solved of level easy or hard.
3. `solve` receives a valid sudoku puzzle from `stdin`. It produces a solved version of that puzzle.

### Assumptions
```
/* No assuptions are made */
```

### Limitations
1. Sudoku only handles ( `creates` or `solves`) only perfect square sized sudokus including 1x1 sudoku. In all other cases, we return sudoku.
2. For sudoku sizes greater than or equal to 25, the runtime is exponentially larger as `solve_sudoku`, and create _sudoku`  methods are recursive.

### Major data structures
1. `puzzle` as the 2D int grid and size holder


### Error handling

1. Sudoku checks the number of parameters and valid arguments, "solve" or "create".
2. Sudoku parser checks that the sudoku is valid. It can have 0 entries, but every nonzero entry must be unique in each column, row, and box.
2. Sudoku build does not return anything as there is not technically any to occur while populating grid. 

### Visual Representation 
The following is the chosen format for printing:

```c
+-------+-------+-------+
| 9 0 5 | 2 7 8 | 3 0 0 | 
| 2 8 0 | 0 0 0 | 6 0 0 | 
| 0 0 0 | 9 6 0 | 8 5 0 | 
+-------+-------+-------+
| 6 0 0 | 0 0 5 | 9 3 4 | 
| 8 0 0 | 0 2 0 | 5 7 0 | 
| 0 0 9 | 0 0 3 | 0 2 0 | 
+-------+-------+-------+
| 0 0 7 | 5 9 6 | 4 0 0 | 
| 0 3 8 | 0 0 0 | 2 6 0 | 
| 4 0 0 | 0 3 0 | 7 0 0 | 
+-------+-------+-------+
```

### Testing plan

*Unit testing*.  A small test program in `testing.sh` to test each module to make sure it does what it's supposed to do.

*Integration testing*.  Assemble the sudoku and test it as a whole using `testing.sh`.
In each case, examine the output files carefully to be sure they have the correct representation of the index data structure. 

*Fuzz testing*. Utilize fuzz testing to test several random grids on the solver to see if they are solved correctly (meaning unique vertical/horizontal rows and 3x3 grids)
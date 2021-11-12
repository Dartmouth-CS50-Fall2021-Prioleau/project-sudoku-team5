# FINAL PROJECT SUDOKU
## IMPLEMENTATION SPEC

## Game description
`Sudoku` is well known logic puzzle where numbers between 1 and n are placed on a nxn grid of cells. The placement of numbers has to follow certain rules. There are many variations of Sudoku, but for this project we implement a general sudoku for all `nxn `grid, where n is a perfect square.

## Rules

In a valid Sudoku grid, every number from 1 to n must appear:

Only once in every row
Only once in every column
Only once in every sqrt(n)xsqrt(n) squared region
The puzzle is presented as a nxn valid grid with some numbers missing. The objective is for the program solving the Sudoku puzzle to fill in missing numbers without violating any of the aforementioned rules.


### Pseudocode for Algorithmic/logic  flow through major functions.


Following the rules of a basic sudoku game, we implement 3 main modules to come up with a working the sudoku program. They are:

1. `create`
2. `solve`
3. `sudoku`

and a major structure `puzzle_t*` which holds the 2D `int` grid array and the size of the sudoku.


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
        2. If we get here, all tired values could not find a solution. Return flase to caller.
3. Return true.

Output: Boolean-> true if solution found, false otherwise.

#### Sudoku 

A. `main` 
1. Parse arguments and creates or solves a sudoku puzzle


### APIs, Interfaces, Function-Prototypes and Parameters

We use the following interfaces and their functions from CS50 `libCS50` library provided in the precceding Labs. They are stored in our `library` directory`:


1. `file.h`

Function prototypes and parameters include:

```c
1.
char *freadwordp(FILE *fp);  Read a word from the file into a null-terminated string, and return a pointer to it; caller must later free() the pointer.
```

2. `memory.h`

Function prototypes and parameters include:

```c
1.
void *count_malloc(const size_t size);Like malloc() but track the number of successful allocations, and, if response is NULL, print error and die.
2.
void *count_calloc(const size_t nmemb, const size_t size);Just like malloc() but track the number of successful allocations.
3.
void count_free(void *ptr);Just like free() but track the number of calls.
```

Additionally, the `create.h`, `solve.h`, and `puzzle.h` modules were created specifically for the sudoku program. The `puzzle.h` provides the interface for the `puzzle_t*` structure. The following are the function prototypes and parameters are for the modules:

`puzzle.h`

Function prototypes and parameters include:

```c
1.
puzzle_t* puzzle_new(int size); Creates a new, square puzzle structure of a given size.
2.
int** get_grid(puzzle_t* puzzle);
Returns the 2-D grid integer array of boxes from a given puzzle_t struct if the puzzle struct is not null. 
3.
int get_grid_size(puzzle_t* puzzle); Return size of grid for a given puzzle
4.
int get_box_value(puzzle_t* puzzle, int x, int y);Return the box struct held at a given coordinate (x,y) on in the 2-D grid of the puzzle_t struct.
5.
bool set_box_value(puzzle_t* puzzle, int value, int x, int y);Set the box_t* pointer at a given (x,y) point in the 2-D array of pointers to a provided box object.
6.
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value, char* level);Returns true if a given value is not present in a puzzle's particular row, column and sub 3X3 grid within the puzzle.
7.
void puzzle_delete(puzzle_t* puzzle); Deletes a puzzle struct by first freeing the grid pointer and finally freeing the puzzlt struct.
8.
int get_num_todelete(puzzle_t* puzzle, char*level); Returns the number of box values to delrte from complet sudoku.
9.
void puzzle_print_simple (FILE* fp, puzzle_t* puzzle);Prints  given sudoku in grid single space format to given output file.
10.
void puzzle_print_formated (FILE* fp, puzzle_t* puzzle);Prints sudoku to console using textual representation with characters "|","*" and "-" to build the grid, white spaces as needed, and integers 0 to 9 to represent numbers.
11.
bool is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry, char* level); Returns true if a given value is  present in a  sub 3X3 box within the puzzle.
12.
bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle); Parses the user sudoku, by checking if it has valid format.
13.
void print_box_value( FILE* fp, int box_value); Prints the given value to the given file.
```

`create.h`

```c
1.
void build_full_sudoku(puzzle_t* puzzle, char* level);  builds a full sudoku from which the puzzle  is is made.
2.
void create_sudoku(puzzle_t* puzzle, char* level); creates a sudoku puzzle but deleting a given number  of entries from a fully solved puzzle. Assumes parsed sudoku is valid.
```

`solve.h`

```c
1.
bool solve_sudoku(puzzle_t* puzzle, int row, int column, char* level); Solves the given puzzle in palce and return true as a sign of success.
2.
int count_num_solutions(puzzle_t* puzzle, char* level); Counts the number of solutions for a given puzzle and returns count to user.
```

### Data Structures

The primary data structures utilized in this lab are:

1. `puzzle_t*`
  - the puzzle pointer structure holds the size of the sudoku puzzle (the length of one of the square grid's sides) and the 2-D `grid` array of `int` values. 


####  Major Unit Fuctions' Underlying Logic 

Analysis of the rules of the simple sudoku allowed for the following are the indespensible sustainable logic when implementing unit functions in modules.

`build full sudoku`






### Security and Privacy Properties

Because this program runs on a local server, issues of privacy that can arise from accessing outside servers or multithreaded client-server connections are not of concern for this program.

### Error Handling and Recovery

If the user erronously enters commands via the command line, the program will print an error to `stderr` and return with a non-zero exit code. 

If an error occurs allocating memory within the program, an error message will be printed, but the program will still run.

### Resource Management

Our two main standards of performance for sudoku are accuracy and efficiency, so we must iterate over the puzzle grid as few times as possible to optimize speed without losing accuracy and boundary-checking. 

This project has 3 team members, Dylan Beinstock, Salifyanji Namwila, and Veronica Quidore.

Each team member, Dylan, Sali, and Veronica, took part in pseudocoding design, coding implementation and documentation and explained their daily progress through in-person meetings and regularly updating their team Github repo. 

### Persistant Storage

The output of `create` mode will be displayed to `stdout` and can be piped into and read by `solve` mode through `stdin`. 

The output of `solve` mode will also be displayed to `stdout`.


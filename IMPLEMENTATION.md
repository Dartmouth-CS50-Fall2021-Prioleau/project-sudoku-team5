# FINAL PROJECT SUDOKU
## IMPLEMENTATION SPEC

### Pseudocode

7 main modules/functions are used in the sudoku program. They are:

1. `box`
2. `puzzle`
3. `build`
4. `unique`
5. `create`
6. `solve`
7. `sudoku`


### Sudoku

1. Execute the command line 
2. Check inputs are valid
    1. correct number of arguements
3. Check if the mode is create or solve
    1. Create:
        1. Create an empty puzzle struct 
            1. For each point in a 9 by 9 array initialize a box struct 
                1. Set the value to 0
                2. Add points 1 through 9 to a counter to track the range of possiblities
                3. Add points 1 through 9 to a counter to track visited points 
        2. Build a full sudoku 
            1. Loop through all points in the grid
            2. Check if the point has a possible options (the number of points that exist in both the range and visited)
                1. If options is 0:
                    1. get the previous point 
                    2. Reset the previous points value to 0
                    3. Reset the previous points visited counter
                    4. Go back to the previous point
                2. If options > 0
                    1. Find a valid point at that point (it exists in the range and hasn't been visited yet)
                    2. Set the box's value to that point
                    3. Update the box to reflect it has been visited
                    4. Go to the next point
        3. Remove points until there are the desired number left (checking for uniqueness as points are removed)
        4. Print the create suddoku
    2. Solve:
        1. Parse the input and build a puzzle struct, setting the values in the struct as the string is parsed
        2. Solve the sudoku
            1. Loop through all points in the grid, skipping those that are in the original grid
            2. Check if the point has a possible options (the number of points that exist in both the range and visited)
                1. If options is 0:
                    1. get the previous point 
                    2. Reset the previous points value to 0
                    3. Reset the previous points visited counter
                    4. Go back to the previous point 
                        1. If the previous point is in the original grid keep going back until a new point is found
                2. If options > 0
                    1. Find a valid point at that point (it exists in the range and hasn't been visited yet)
                    2. Set the box's value to that point
                    3. Update the box to reflect it has been visited
                    4. Go to the next point

# Sudoku Method and Implementation

1. Main: Parse arguments and creates or solves a sudoku puzzle

```c
int main(const int argc, const char** argv)
```

2. parse_user_sudoku: Build a puzzle struct from a given input

```c
bool parse_user_sudoku(FILE* fp, puzzle_t* puzzle, char* level)
```

3. build_sudoku: Creates a full, valid sudoku

```c
void build_sudoku(puzzle_t* puzzle, char* level)
```

4. count_num_solutions: Determines how many solutions the current, incomplete sudoku board has

```c
int count_num_solutions(puzzle_t* puzzle, char* level) 
```

5. sudoku_create_puzzle: Takes a completed puzzle and removes points until the desired size is reached

```c
void sudoku_create_puzzle(puzzle_t* puzzle, char* level)
```

6. solve_backtrack_sudoku: Take an incomplete sudoku and solve it 

```c
void solve_backtrack_sudoku(puzzle_t* puzzle)
```

### APIs, Interfaces, Function-Prototypes and Parameters

We use the following interfaces and their functions from Sali's Lab 3 and the TSE Library. They are stored in our `library` directory`:

1. `counters.h`

Its function prototypes and parameters include: 

```c
counters_t *counters_new(void);
int counters_add(counters_t *ctrs, const int key);
int counters_get(counters_t *ctrs, const int key);
bool counters_set(counters_t *ctrs, const int key, const int count);
void counters_print(counters_t *ctrs, FILE *fp);
void counters_iterate(counters_t *ctrs, void *arg, 
                      void (*itemfunc)(void *arg, 
                                       const int key, const int count));
void counters_delete(counters_t *ctrs);
```

2. `file.h`

Its function prototypes and parameters include: 

```c
char *freadwordp(FILE *fp);
```

3. `memory.h`

Its function prototypes and parameters include:

```c
void *count_malloc(const size_t size);
void *count_calloc(const size_t nmemb, const size_t size);
void count_free(void *ptr);
```

Additionally, the `box.h` and `puzzle.h` interfaces for the `box_t*` and `puzzle_t*` data structures were created specifically for the sudoku program. Their function prototypes and parameters are:

`box.h` 

```c
box_t* box_new(int size_of_grid);
counters_t* get_visited(box_t* box);
void box_value_print(box_t* box, FILE* fp);
counters_t* get_counter(box_t* box);
void set_value(box_t* box, int val);
int get_value(box_t* box); 
int get_grid_size_from_box(box_t* box);
void box_delete(box_t *box);
void reset_box(box_t* box);
void reset_visited(box_t* box);
```

`puzzle.h`

```c
puzzle_t* puzzle_new(int size);
box_t*** get_grid(puzzle_t* puzzle);
void puzzle_print (puzzle_t* puzzle, FILE* fp);
void valid_add(puzzle_t* puzzle, int x, int y, int* value, int reset);
box_t* get_box_from_grid(puzzle_t* puzzle, int x, int y);
void set_box_in_grid(puzzle_t* puzzle, box_t* box, int x, int y);
int get_grid_size(puzzle_t* puzzle);
void puzzle_iterate(puzzle_t* puzzle);
void puzzle_delete(puzzle_t* puzzle);
void update_all_box_counters(puzzle_t* puzzle);
void update_adjacent_box_counters(puzzle_t* puzzle, int x, int y, int value);
int get_box_value(puzzle_t* puzzle,int  x, int y);
int get_box_count(puzzle_t* puzzle,int  x, int y, int value);
int get_visit_count(puzzle_t* puzzle,int  x, int y, int value);
void reset_adjacent_box_counters(puzzle_t* puzzle, int x, int y, int value) ;
void reset_all(puzzle_t* puzzle) ;
void sudoku_populate(puzzle_t* puzzle);
void sudoku_print_simple(puzzle_t* puzzle, FILE *fp);
voidsudoku_print_formated (puzzle_t* puzzle, FILE *fp);
```

### Data Structures

The three primary data structures utilized in this lab are:

1. `puzzle_t*`
  - the puzzle pointer structure holds the size of the sudoku puzzle (the length of one of the square grid's sides) and the 2-D `grid` array of `box_t` structs. 
2. `box_t*`
  - the box pointer structure holds the integer `size` of one side of the overall puzzle grid it inhabits, the integer `value` of an individual box displayed to the user, the box's integer `x-coordinate` and `y-coordinate` on the grid, and the `range` and `visited` countersets.
3. `counters_t*`(all credit to Salifyanji Namwila... this data structure is recycled from her Lab 3)
  - there are two counterset structures within the box structure. They are `range`, which keeps track of the possible values, and `visited`, which keeps track of the already-tried values for a given box.

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
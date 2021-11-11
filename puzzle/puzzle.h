/*
 * puzzle.h - a header file for the CS50 Sudoku Final Project "puzzle" module
 * 
 * Authors: Dylan Beinstock, Salifyanji J. Namwila, and Veronica Quidore
 *
 * a puzzle holds a 2-D array of box_t pointers and the integer size of that array. 
 *  -> size is the length of a row or column for a given square grid puzzle.
 * to make a puzzle, simply call puzzle_new(int size)
 * to delete the puzzle, call puzzle_delete(puzzle)
 * 
 */ 

#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../library/memory.h"

/**************** global types ****************/
typedef struct puzzle puzzle_t;

/********************** functions *******************/

/********************* puzzle_new() *********************/
/* Create a new, square puzzle structure of a given size
 * The structure holds the size of one side (row or column) and a "grid" that is a 2-D array of `box_t* pointers
 * The caller provides: 
 *  - a size integer
 * We return:
 *  - an puzzle structure that holds the size of the grid and a 2-D grid of empty box_t* structures
 *  - null if the memory for the puzzle struct or the grid cannot be allocated
 * 
 * We malloc memory for the puzzle_t struct calloc memory for the grid structure. 
 * The user is responsible for freeing the memory through puzzle_delete.
 */ 
puzzle_t* puzzle_new(int size);


/********************* get_grid() *********************/
/* Return the 2-D grid integer array of boxes from a given puzzle_t struct if the puzzle struct is not null. 
 * Otherwise, return null.
 * 
 * The user provides: a valid puzzle struct
 * We return: the 2-D grid of the puzzle struct
 */ 
int** get_grid(puzzle_t* puzzle);


/***************************  get_grid_size() *****************/
/* Return size of grid for a given puzzle
 * Return NULL if  puzzle is NULL
 * User provides puzzle 
*/
int
get_grid_size(puzzle_t* puzzle);

void print_box_value( FILE* fp, int box_value);


/********************* get_box_value() *********************/
/* Return the box struct held at a given coordinate (x,y) on in the 2-D grid of the puzzle_t struct
 * 
 * The user provides:
 *  - a valid puzzle struct
 *  - an x and y int value of [0,size of puzzle_t]
 * 
 * We return:
 *  - NULL, if inputs invalid
 *  - The box at the given coordinates in the grid, if inputs are valid
 */ 
int
 get_box_value(puzzle_t* puzzle, int x, int y);


/********************* set_box_value() *********************/
/* Set the box_t* pointer at a given (x,y) point in the 2-D array of pointers to a provided box object
 * User provides: 
 *  - a non-null puzzle struct and box struct
 *  - an x and y int value of [0,size of puzzle_t]
 * 
 * We return:
 *  nothing, but we set the grid pointer at the given coordinates to the provided box.
 */
bool
set_box_value(puzzle_t* puzzle, int value, int x, int y);



/**************************  val_not_in_cross_section() ***************************/
/* Returns true if a given value is not present in a puzzle's
 * particular row, column and sub 3X3 grid within the puzzle
 *
 *User provides a valid puzzle, row, column, and value to check for.
 * We return true if value is not present in given row, column, and 3X3 sub grid
 * We return false otherwise;
 * 
*/
bool
val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value);



/**************************  is_val_in_box() ***************************/
/* Returns true if a given value is  present in a  sub 3X3 box within the puzzle
 * particular row, column and sub 3X3 grid within the puzzle
 *
 *User provides a valid puzzle, row, column, and value to check for annd the start of the diagonal to check in.
 * We return true if value is present in given row, column, and 3X3 sub grid
 * We return false otherwise;
 * 
*/
bool 
is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry, char* level);

/********************* puzzle_delete() *********************/
/* Delete a non-null puzzle struct by calling the box_delete function to free its boxes in the grid 
 * and count_free to free the grid 2-D array of pointers and the puzzle_t struct memory allocated
 * 
 * User provides:
 *  - non-null puzzle struct
 * We return:
 *  - nothing, but we do free all of the memory. User is responsible for calling this function if they call puzzle_new()
 */
void
puzzle_delete(puzzle_t* puzzle);


/******************** sudoku_print ***************/
/*  Prints  given sudoku in grid format to given output file.
 * Caller provides an output file 
 * and the sudoku to print. For example:
 * 
3 4 0 6 0 0 4 8 7 
0 0 2 9 0 0 0 0 0 
0 8 0 0 4 0 8 0 5 
0 0 7 8 1 0 2 0 4 
0 0 2 0 9 0 0 0 8 
0 0 0 3 8 0 0 9 0 
0 3 8 0 0 6 6 0 0 
0 0 0 1 3 9 8 9 8 
6 0 6 0 8 3 0 0 0 
 */
void
puzzle_print_simple (FILE* fp, puzzle_t* puzzle);


/*************************  sudoku_print_formated () ****************************/
/* Prints sudoku to console using textual representation with characters "|"and "__ "
 * to build the grid, white spaces as needed, and integers 0 to 9 to represent numbers
 * in the puzzle with 0 representing a missing number. For example:
+-------+-------+-------+
| 3 4 0 | 6 0 0 | 4 8 7 | 
| 0 0 2 | 9 0 0 | 0 0 0 | 
| 0 8 0 | 0 4 0 | 8 0 5 | 
+-------+-------+-------+
| 0 0 7 | 8 1 0 | 2 0 4 | 
| 0 0 2 | 0 9 0 | 0 0 8 | 
| 0 0 0 | 3 8 0 | 0 9 0 | 
+-------+-------+-------+
| 0 3 8 | 0 0 6 | 6 0 0 | 
| 0 0 0 | 1 3 9 | 8 9 8 | 
| 6 0 6 | 0 8 3 | 0 0 0 | 
+-------+-------+-------+
 */

void 
puzzle_print_formated (FILE* fp, puzzle_t* puzzle);


/*********************** parse_user_puzzle() *****************************/
/*
 *
 *
 * 
 */
bool
parse_user_puzzle(FILE* fp, puzzle_t* puzzle);



#endif // __PUZZLE_H 

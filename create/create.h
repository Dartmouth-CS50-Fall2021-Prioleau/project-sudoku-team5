/*
 * create.h - header file for CS50 'create' module
 * 'create.h' comprises all methods/ functions neccessary in 
 * creating a sudoku puzzle.
 * the sudoku create  fuction, for instance creates a newly initialised
 * sudoku. The caller could later use this emply sudoku to create a puzzle
 * according to choice of dificulty.
 * 
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 * 
 * Authors:
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 * 
*/

#ifndef __CREATE_H
#define __CREATE_H

#include <stdio.h>
#include <stdbool.h>
#include "../library/counters.h"
#include "../common/box.h"

/*************************** global types ***********************/
/* none */

/*************************** functions *************************/

/*************************** sudoku_create() **********************/
/* see create.h for description */
/* creates a newly initialized sudoku and return a pointer to the sudoku  to caller.
 * Caller provides a desired SIZE of sudoku.
 * We create a 2D new sudoku  and initialize each position in the
 * array with a new box structure. 
*/
void sudoku_new(box_t* sudoku[9][9], const int SIZE);


/******************** sudoku_print ***************/
/*  Prints  given sudoku in grid format to given output file.
 * Caller provides an output file 
 * and the sudoku to print. For example
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
void sudoku_print (box_t* sudoku[9][9], FILE *fp);


/*************************  sudoku_print_formated () ****************************/
/* Prints sudoku to console using textual representation with characters "|"and "__ "
 * to build the grid, white spaces as needed, and integers 0 to 9 to represent numbers
 * in the puzzle with 0 representing a missing number. For example
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
sudoku_print_formated (box_t* sudoku[9][9], FILE *fp);


/************************** sudoku_unsolved() **********************/
/* Buils from scratch  an unsolved but solvable sudoku puzzle
 * User provides a new (init valuues == 0) sudoku, and the level of difficulty desired
 * If level is invaalid, we print an error to std and return.
 * If sudoku is invalid we print error message and return.
 * We build a an *inplace* randomized sudoku from scratch.
 */

void
sudoku_unsolved(box_t* sudoku[9][9], char* level);


/**************************** sudoku_update_rows_cols_box() **************************/
/* description of method here...
 *
 *
 * 
 * 
 * 
 * 
 */
void sudoku_update_rows_cols_box(box_t* sudoku[9][9], int random_box_x, int random_box_y, int key_value, char* level);



/**************************************   val_not_in_cross_section() ************************************/
bool val_not_in_cross_section(box_t* sudoku[9][9], int row, int column, int value, char* level);

void sudoku_create_puzzle(box_t* sudoku[9][9], char* level);

int count_num_solutions(box_t* sudoku[9][9], char* level) ;

#endif // __CREATE_H


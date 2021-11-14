/* 
 * create.c - CS50 Sudoku Project 'create' module
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *  
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 *
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 * 
*/


#ifndef __SOLVE_H
#define __SOLVE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../puzzle/puzzle.h"


/*************************** global types ***********************/
/* none */

/*************************** functions *************************/
/*************************** solve_sudoku() **********************/
/* Solves the given puzzle in palce and return true as a sign of success
 * Returns false otherwise.
 * User provides puzzle to solve, the row and column to start from 
 * and the level of puzzle to solve
 *
 */
bool solve_sudoku(puzzle_t* puzzle, int row, int column, char* level);



/********************** count_num_solutions() *************************/
/* Counts the number of solutions for a given puzzle and returns count to user.
 * Calls helper method that actually does the counting
 *
*/
int count_num_solutions(puzzle_t* puzzle, char* level);


#endif // __SOLVE_H


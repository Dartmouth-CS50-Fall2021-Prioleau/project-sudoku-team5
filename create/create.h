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


#ifndef __CREATE_H
#define __CREATE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "../puzzle/puzzle.h"
//#include "../solve/solve.h"


/*************************** global types ***********************/
/* none */

/*************************** functions *************************/

/*************************** create_ sudoku() **********************/
/* creates a sudoku puzzle but deleting a given number  of 
 * entries from a fully solved puzzle.
 * Caller provides a fully solved sudoku(with unique solution) and deisred level of sudoku.
 * We create a 2D sudoku puzzle inplace
 * 
*/
void
create_sudoku(puzzle_t* puzzle, char* level);



/*************************** build_full_sudoku() **********************/
/* builds a full sudoku from which the puzzle  is is made.
 * 
 * Caller provides a new empty puzzle  and desired level of sudoku.
 * We create a 2D sudoku puzzle inplace
 * 
*/

void build_full_sudoku(puzzle_t* puzzle, char* level);

#endif // __CREATE_H


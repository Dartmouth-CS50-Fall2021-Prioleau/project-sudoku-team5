#ifndef __BUILD_H
#define __BUILD_H

#include <stdio.h>
#include <stdbool.h>
#include "../puzzle/puzzle.h"

/*************************** build_sudoku() **********************/
/* Takes in a puzzle and a mode
 * The following method using backtracking to either 
 * 1) create a new, full sudoku
 * 2) Solve an incomplete sudoku board
 * 
 * We create a 2D new sudoku  and initialize each position in the
 * array with a new box structure. 
*/
bool build_sudoku(puzzle_t* puzzle, char* mode);

#endif // __BUILD_H

#ifndef __SOLVE_H
#define __SOLVE_H

#include <stdio.h>
#include <stdbool.h>
#include "../library/counters.h"
#include "../box/box.h"


void solve_sudoku(box_t* sudoku[9][9]);

void horizontal_update(int x, int y, int value, box_t* sudoku[9][9]);

void vertical_update(int x, int y, int value, box_t* sudoku[9][9]);

void box_update(int x, int y, int value, box_t* sudoku[9][9]) ;

#endif // __CREATE_H


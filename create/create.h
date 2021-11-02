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
#include "counters.h"
#include "box.h"

/*************************** global types ***********************/
/* none */

/*************************** functions *************************/

/*************************** sudoku_create() **********************/
/* see create.h for description */
/* creates a newly initialized sudoku and return a pointer to the sudoku  to caller.
 * Caller provides a desired SIZE of sudoku.
 * We create a 2D new sudoku  and initialize each position in the
 * array with a new box structure. 
 *
*/
box_t** sudoku_new(const int SIZE);

#endif // __CREATE_H

/* 
 * create.c - CS50 Sudoku Project 'create' module
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *  
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "counters.h"
#include "box.h"



/**************** file-local global variables ****************/
/* none */



/***************************** global functions ****************/
/* that is, visible outside this file */

/*************************** sudoku_create() **********************/
/* see create.h for description */

 box_t**
sudoku_new(const int SIZE){
     
     
    box_t** sudoku[SIZE][SIZE] ; // allocate space for 2D array  of size SIZE on stack 

    for(int i=0;  i < SIZE ; i++) // rows
    { 
        for (int j = 0; j < SIZE; j++) // columns
        {
            sudoku[i][j] =  box_new(); // put a new box at each position in the 2D array/sudoku 
        }
    }
    return sudoku; // return the newly initialized sudoku to caller

}










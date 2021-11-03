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
#include "../library/counters.h"
#include "../common/box.h"



/************************** file-local global variables   ***********************/
/* none */


/************************  static helper  functions  prototypes ******************/
/* that is, not visible outside this file */
static void valueprint(FILE* fp, int value);
static void sudoku_update_rows_cols_box(box_t* sudoku[9][9], int x, int y, int value, char* level);
//static int get_rand_box_val(box_t* box, box_t* sudoku[9][9]);

/***************************** global functions *********************************/
/* that is, visible outside this file */

/******************************* sudoku_create() ********************************/
/* see create.h for description */

 void 
 sudoku_new( box_t* sudoku[9][9], const int SIZE){
     
     // handle NULL sudoku
    if(sudoku == NULL){
        return;
    }
    for(int i=0;  i < SIZE ; i++) // rows
    { 
        for (int j = 0; j < SIZE; j++) // columns
        {
            sudoku[i][j] =  box_new(); // put a new box at each position in the 2D array/sudoku 
        }
    }

}


/******************************* sudoku_print() *************************************/
/* see create.h for description  */
void
sudoku_print (box_t* sudoku[9][9], FILE* fp,  void (*itemprint)(FILE* fp, void* item)){
    
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(sudoku == NULL){
        printf("(null)");
        return;
    }
    for( int i = 0; i < 9; i++){  // row
        for(int j= 0 ;j < 9; j++){  // column
           box_value_print(sudoku[i][j],fp, valueprint); 
        }
        fprintf(fp, "\n"); // print next row of sudoku
    }

}





/******************************************************************************************/
/******************************************************************************************/
/***************** static    helper   methods   defined   here   **************************/
/******************************************************************************************/
/******************************************************************************************/
/* that is, not visible outside this file */

/********************* valueprint() ***********************/
/* helper method that prints the box value to  given file
 *
 */
static void valueprint(FILE* fp, int value)
{  
    int value = value;
    if(value != NULL){
        fprintf(fp, "%d ", value); 
  }
}

static void sudoku_update_rows_cols_box(box_t* sudoku[9][9], int x, int y, int value, char* level)
{
    for (int i = 0; i < 9; i++) {
        // set each key corresponding to the value in the relevant box counters to 0 within the row
    }
    for (int j = 0; j < 9; j++) {
        // set each key corresponding to the value in the relevant box counters to 0 within the column
    }
    
}
// static int get_rand_box_val(box_t* box, box_t* sudoku[9][9])
// {

// }

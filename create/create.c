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
static char* normalize_word(char* word);

/***************************** global functions *********************************/
/* that is, visible outside this file */

/******************************* sudoku_create() ********************************/
/* see create.h for description */

 void 
 sudoku_new(box_t* sudoku[9][9], const int SIZE)
 {
     
     // handle NULL sudoku
    if(sudoku == NULL){
        return;
    }
    for(int i=0;  i < SIZE ; i++) // rows
    {   
        for (int j = 0; j < SIZE; j++) // columns
        { 
          
          sudoku[i][j] = malloc(sizeof(box_t*));
          sudoku[i][j] =  box_new(); // put a new box at each position in the 2D array/sudoku 
            sudoku[i][j] =  box_new(); // put a new box at each position in the 2D array/sudoku 
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
           box_value_print(sudoku[i][j],fp, NULL); 
        }
        printf("\n"); // print next row of sudoku
    }

}

/************************** sudoku_unsolved() **********************/
/* see create.h for description  */

void
sudoku_unsolved(box_t* sudoku[9][9], char* level){
/* see create.h for description */
    
    // nomalize level input
    normalize_word(level);
    int num_repeats;
    if (strcmp(level, "easy") == 0){
        num_repeats = 37;
       // for 37 times, do the following
    }
    else if(strcmp(level, "hard") == 0){
        num_repeats = 25;
    }
    else{
        printf(sterr, "Invalid level: Enter easy(or EASY) or hard(or HARD");
        return;
    }
       
    for(int i = 0; i < num_repeats: i++){
        // pick a random box in the grid until found one with value zero
        // current x,y values
        int random_box_x;
        int random_box_y;

        do{
            // pick a random x
            random_box_x = rand() % 8 // from 0 to 8 

            //pick a random y
            random_box_y = rand() % 8 // from 0 to 8
                
        }
        // check if the box at that location has values of zero
        // while we haven't found one, keep picking random x,y locations
        while(sudoku[random_box_x][random_box_y]->value != 0);
                
            // keep cuurent random key and value 
            int random_key;
            int key_value;
                
            // next pick key from counter until found one whose key value is 1
            do{
                // pick a random key between 1 and 9 
                random_key = (rand() % 9 )+ 1 // from 1 to 9
            }
            //gey key value form box's counterset
            key_value = counters_get(sudoku[random_box_x][random_box_y]->ctr, random_key);

            // check if value of key in that box's counterset is 1
            // while its not, keep picking keys
            while(key_value !=1);

            // set the key's value as value of the box
            sudoku[random_box_x][random_box_y]->value = random_key; 

            // update relevant coresponding row, cols, and box->ctr possible values affected by choice of key
            sudoku_update_rows_cols_box(box*t sudoku[9][9], int random_box_x, int random_box_y, int key_value, char* level) // Veronica's to do
    }  

//     // verify that the unsolved sudoku is solvable before returning to user.
//    if(!isSolvable(box_t* sudoku, char* level)){ //  method not-existent yet
//         // rebuild if unsolvable
//         sudoku_unsolved(sudoku, level);    
//     }

}

void sudoku_update_rows_cols_box(box*t sudoku[9][9], int random_box_x,int random_box_y, int key_value, char* level){
    // to do
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

/*********************** normalize_word() *************************/
/*Author: Salifyanji J Namwila 
 *
 * Coverts a given word to all-lower case and returns the  word to caller
 * Input: a string , char*, word 
 * Output: lower-case version of the  same word
 * return null toif word is NULL
 * 
 */
static char* normalize_word(char* word)
{
    for(int i = 0; i <= (strlen(word)); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}




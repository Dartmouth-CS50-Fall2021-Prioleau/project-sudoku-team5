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
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "../library/counters.h"
#include "../common/box.h"



/************************** file-local global variables   ***********************/
/* none */


/************************  static helper  functions  prototypes ******************/
/* that is, not visible outside this file */
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

        }
    }

}


/******************************* sudoku_print() *************************************/
/* see create.h for description  */
void
sudoku_print (box_t* sudoku[9][9], FILE* fp){
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
           box_value_print(sudoku[i][j],fp); 
        }
        printf("\n"); // print next row of sudoku
    }

}



/******************************* sudoku_print() *************************************/
/* see create.h for description  */
void
sudoku_print_formated (box_t* sudoku[9][9], FILE* fp){
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(sudoku == NULL){
        printf("(null)");
        return;
    }


    printf("+-------+-------+-------+\n");
     
    // the  3 3X3 sudoku's in the first row
    for ( int i = 0; i< 3; i++){  //first three rows

        for(int j= 0 ;j < 9; j++){ // all their collumns

            // start of column
            if(  j == 0 ){
                printf("| ");
                box_value_print(sudoku[i][j],fp);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 box_value_print(sudoku[i][j],fp);
                 printf("| ");
             }
            else{
                box_value_print(sudoku[i][j],fp); 
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");


    // the  3 3X3 sudoku's in the second row
    for ( int i = 3; i< 6; i++){

        for(int j= 0 ;j < 9; j++){

            // start of column
            if(  j == 0 ){
                printf("| ");
                box_value_print(sudoku[i][j],fp);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 box_value_print(sudoku[i][j],fp);
                 printf("| ");
             }
            else{
                box_value_print(sudoku[i][j],fp); 
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");



    // the  3 3X3 sudoku's in the third(last) row
    for ( int i = 6; i< 9; i++){  // last three rows

        for(int j= 0 ;j < 9; j++){ // all their columns

            // start of column
            if(  j == 0 ){
                printf("| ");
                box_value_print(sudoku[i][j],fp);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 box_value_print(sudoku[i][j],fp);
                 printf("| ");
             }
            else{
                box_value_print(sudoku[i][j],fp); 
            }
        }printf("\n"); // print next row of sudoku     
    } printf("+-------+-------+-------+\n"); // of sudoku line
}




/************************** sudoku_unsolved() **********************/
/* see create.h for description  */

void
sudoku_unsolved(box_t* sudoku[9][9], char* level){
   // ensure non- seed randomization here
    srand(time(NULL));

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
        fprintf(stderr, "Invalid level: Enter easy(or EASY) or hard(or HARD). \n\n");
        return;
    }

    for(int i = 0; i < num_repeats; i++){

        // pick a random box in the grid until found one with value zero
        // current x,y values
        int random_box_x;
        int random_box_y;

        do{
            // pick a random x
            random_box_x = rand() % 9; // from 0 to 8

            //pick a random y
            random_box_y = rand() % 9; // from 0 to 9
                
        }
        // check if the box at that location has values of zero
        // while we haven't found one, keep picking random x,y locations
        while(get_value(sudoku[random_box_x][random_box_y]) != 0);
                
            // keep cuurent random key and value 
            int random_key;
            int key_value;
                
            // next pick key from counter until found one whose key value is 1
            do{
                // pick a random key between 1 and 9 
                random_key = (rand() % 9 )+ 1; // from 1 to 9

                //gey key value form box's counterset
                counters_t* curr = get_counter(sudoku[random_box_x][random_box_y]);
                key_value = counters_get(curr, random_key);

            }

            // check if value of key in that box's counterset is 1
            // while its not, keep picking keys
            while(key_value !=1);

            // set the key's value as value of the box
            set_value(sudoku[random_box_x][random_box_y], random_key);
            //sudoku[random_box_x][random_box_y]->value = random_key; 

            // update relevant coresponding row, cols, and box->ctr possible values affected by choice of key
            //sudoku_update_rows_cols_box(sudoku[9][9], random_box_x, random_box_y, key_value, level); // Veronica's to do  
    }  
}
/*******************************  sudoku_update_rows_cols_box *****************************/
void sudoku_update_rows_cols_box(box_t* sudoku[9][9], int random_box_x,int random_box_y, int key_value, char* level){
    // to do
}

/******************************************************************************************/
/******************************************************************************************/
/***************** static    helper   methods   defined   here   **************************/
/******************************************************************************************/
/******************************************************************************************/
/* that is, not visible outside this file */

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



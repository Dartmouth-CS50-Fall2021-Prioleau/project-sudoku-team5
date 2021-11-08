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
#include "../box/box.h"



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
        fprintf(stderr, "Invalid level: Enter easy(or EASY) or hard(or HARD");
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
            random_box_y = rand() % 9; // from 0 to 8
                
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
                //counters_t* curr = get_counter(sudoku[random_box_x][random_box_y]);
                //key_value = counters_get(curr, random_key);

            }

            // check if value of key in that box's counterset is 1
            // while its not, keep picking keys
            while(((is_val_in_cross_sect(sudoku, random_box_x, random_box_y, random_key) == random_key)));

            // set the key's value as value of the box
            set_value(sudoku[random_box_x][random_box_y], random_key);
            //sudoku[random_box_x][random_box_y]->value = random_key; 

            // update relevant coresponding row, cols, and box->ctr possible values affected by choice of key

            //sudoku_update_rows_cols_box(sudoku[9][9], random_box_x, random_box_y, key_value, level); // Veronica's to do  
    }  
}






/*************************************** create_sudoku_puzzle() ****************************************/
void sudoku_create_puzzle(box_t* sudoku[9][9], char* level){

    // initialize non- seed randomization
    srand(time(NULL));
    
    // nomalize dificulty level 
    normalize_word(level);
    int num_to_delete;

    //  if easy dificulty,  delete 44 slots
    if (strcmp(level, "easy") == 0){
        num_to_delete = 44;
    
    }
     //  if hard  dificulty for, delete 56 slots
    else if(strcmp(level, "hard") == 0){
        num_to_delete = 56 ;
    }
    // print error and return if level is invalid
    else{
        fprintf(stderr, "Invalid level: Enter easy(or EASY) or hard(or HARD). \n\n");
        return;
    }



    ///////////////////////////////////////////////
    // delete 44 box_values if num_to_delete == 44, 56 if num_to_delete == 56
    for(int i = 0; i <  num_to_delete; i++){
        int x_todelete; // x postion of random box to delete
        int y_todelete; // y postion of random box to delete

        // check if solution of puzzle would be unique if val at x_todelete, y_todelete is actually deleted
        bool is_unique_solution = true;
    do{
        

        do{
            // pick a random x to delete
            x_todelete = rand() % 9; // from 0 to 8

            //pick a random y
            y_todelete = rand() % 9; // from 0 to 8
                
        }
        // check if the box at that location has already been deleted
        // while we haven't found one that has  already been deleted , keep picking random x,y locations until we find one not yet deleted
        while(get_value(sudoku[ x_todelete][ y_todelete]) == 0);

        // once we find one, remember it and see if solution the sudoku would have while that value is deleted is unique
        int to_delete_value = get_value(sudoku[ x_todelete][ y_todelete]);

        // delete value 
        set_value(sudoku[ x_todelete][ y_todelete], 0);

        //and check that solution produced is unique
        is_unique_solution = (count_num_solutions(sudoku,level) == 1);

         // if solution is not unique, put it back
        if(!is_unique_solution){
            //sudoku_print(sudoku, stdout);
            printf("putting back %d\n", to_delete_value);
            set_value(sudoku[ x_todelete][ y_todelete], to_delete_value);
 
        }
        // if solution is unique
        else{
            is_unique_solution = true; // continue to next deletion
        }
    }
    while(!is_unique_solution);
   }
   //sudoku_print(sudoku, stdout);
   //return sudoku;
} 





/********************** count_num_solutions() *************************/
/*
 *
 *
 * 
 * 
 * 
 */
int count_num_solutions(box_t* sudoku[9][9], char* level) 
{   
    // call solution counter
    return count_num_solutions_helper(sudoku,level, 0, 0, 0);
}



/********************** count_num_solutions_helper() *************************/
/*
 *
 *
 * 
 * 
 * 
 */
static int count_num_solutions_helper(box_t* sudoku[9][9], char*level, int num_solutions, int init_row, int init_column)
{
    // bases case
    //check what rows boxs have been seen
    
    // if  init_row init_columns are at the end, we've visited all.
    if(init_row == 9 && init_column == 9)
    {
        return num_solutions+1;
    }

    // visit all boxes not yet seen left to right top to bottom
    for(int i= init_row; i < 9; i++)
    {
        int j = (i == init_row) ? init_column : 0;

        for( ; j < 9; j++)
        {
            // check if the value of the box  at that location is empty
            if(get_value(sudoku[i][j]) == 0)
            {    
                for(int value=1; value<=9; value++)
                {
                    // check that value of sudoku is a valid possible value of box 
                    if(val_not_in_cross_section(sudoku, i, j, value, level))
                    {    
                        
                        set_value(sudoku[i][j], value);

                        // count_num of solution of that sub sudoku with new value
                        if(j == 8){
                          num_solutions = count_num_solutions_helper(sudoku, level, num_solutions, i+1, 0);
                        }else
                        {
                          num_solutions = count_num_solutions_helper(sudoku, level, num_solutions, i, j+1);
                        }
                        set_value(sudoku[i][j], 0); // back track
                    }

                }// some entries did not work so unsolvable
                return num_solutions;
            }
        }


//     // verify that the unsolved sudoku is solvable before returning to user.
//    if(!isSolvable(box_t* sudoku, char* level)){ //  method not-existent yet
//         // rebuild if unsolvable
//         sudoku_unsolved(sudoku, level);    
//     }

}
// return the value if the value is in the row, column, or 3x3, return 0 otherwise
int is_val_in_cross_sect(box_t* sudoku[9][9], int curr_x, int curr_y, int value)
{
    for (int i = 0; i < 9; i++) {  // iterate over column
        if (get_value(sudoku[curr_x][i]) == value) {
            return value;
        }
    }


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



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
#include "../puzzle/puzzle.h"
#include "../common/unique.c"



/************************** file-local global variables   ***********************/
/* none */


/************************  static helper  functions  prototypes ******************/
/* that is, not visible outside this file */
static void valueprint(FILE* fp, int value);
static char* normalize_word(char* word);

/***************************** global functions *********************************/
/* that is, visible outside this file */
void remove_sudoku(puzzle_t* puzzle, int num_left) ;

void sudoku_new(puzzle_t* puzzle, const int SIZE);
void sudoku_unsolved(puzzle_t* puzzle, char* level);
void create_sudoku(puzzle_t* puzzle, char* level);
int count_num_solutions(puzzle_t* puzzle, char* level) ;
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value, char* level);











/******************************* sudoku_create() ********************************/
/* see create.h for description */

/*************************************** create_sudoku_puzzle() ****************************************/
void create_sudoku(puzzle_t* puzzle, char* level){

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
        while(get_box_value(puzzle, x_todelete, y_todelete) == 0);

        // once we find one, remember it and see if solution the sudoku would have while that value is deleted is unique
        int to_delete_value = get_box_value(puzzle, x_todelete, y_todelete);

        // delete value 
         set_value(get_box_from_grid(puzzle,x_todelete,y_todelete), 0);

        //and check that solution produced is unique
        is_unique_solution = (count_num_solutions(puzzle, level) == 1);

         // if solution is not unique, put it back
        if(!is_unique_solution){
            //sudoku_print(sudoku, stdout);
            printf("putting back %d\n", to_delete_value);
             set_value(get_box_from_grid(puzzle,x_todelete,y_todelete), to_delete_value);
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




/***********************************BAD*************************************/


/************************** sudoku_unsolved() **********************/
/* see create.h for description  */
/*
void
sudoku_unso(puzzle_t* puzzle, char* level)
{
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

        // keep cuurent random key and value 
        int random_key;
        int key_value;
        int valid;

            // next pick key from counter until found one whose key value is 1
            do{

              do{
                // pick a random x
                random_box_x = rand() % 9; // from 0 to 8

                //pick a random y
                random_box_y = rand() % 9; // from 0 to 9
              }
              // check if the box at that location has values of zero
              // while we haven't found one, keep picking random x,y locations
              while(get_box_value(puzzle,random_box_x,random_box_y) != 0);


                // pick a random key between 1 and 9 
                random_key = (rand() % 9 )+ 1; // from 1 to 9
                
                //gey key value form box's counterset
                key_value = get_box_count(puzzle, random_box_x,random_box_y, random_key);

                valid = random_key;

                if(key_value == 1) {
                  valid_add(puzzle, random_box_x, random_box_y, &valid, random_key);
                }

            }

            // check if value of key in that box's counterset is 1
            // while its not, keep picking keys
            while(key_value !=1 && valid != -1);


            // set the key's value as value of the box
            set_value(get_box_from_grid(puzzle,random_box_x,random_box_y), random_key);

            for(int k = 1; k <= 9; k ++) {
              counters_set(get_counter(get_box_from_grid(puzzle, random_box_x, random_box_y)), k, 0);
            }

            // update relevant coresponding row, cols, and box->ctr possible values affected by choice of key
            update_adjacent_box_counters(puzzle, random_box_x,random_box_y, random_key);

    }  
}
*/

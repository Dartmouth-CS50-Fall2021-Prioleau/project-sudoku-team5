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



/************************** file-local global variables   ***********************/
/* none */


/************************  static helper  functions  prototypes ******************/
/* that is, not visible outside this file */
static void valueprint(FILE* fp, int value);
static char* normalize_word(char* word);

/***************************** global functions *********************************/
/* that is, visible outside this file */
void sudoku_populate(box_t* sudoku[9][9]);
void remove_sudoku(box_t* sudoku[9][9], int num_left) ;

void sudoku_new(box_t* sudoku[9][9], const int SIZE);
void sudoku_print (box_t* sudoku[9][9], FILE* fp);
void sudoku_print_formated (box_t* sudoku[9][9], FILE* fp);
void sudoku_unsolved(puzzle_t* puzzle, char* level);
void sudoku_create_puzzle(box_t* sudoku[9][9], char* level);
int count_num_solutions(box_t* sudoku[9][9], char* level) ;
bool val_not_in_cross_section(box_t* sudoku[9][9], int row, int column, int value, char* level);

/******************************* sudoku_create() ********************************/
/* see create.h for description */



                
                //gey key value form box's counterset
                //counters_t* curr = get_counter(sudoku[random_box_x][random_box_y]);
                //key_value = counters_get(curr, random_key);

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

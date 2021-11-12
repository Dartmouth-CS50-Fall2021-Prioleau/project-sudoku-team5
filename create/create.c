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
#include <math.h>
#include <time.h>
#include "../puzzle/puzzle.h"
#include "../solve/solve.h"
#include "create.h"


/************************** file-local global variables   ***********************/
/* none */


/************************  static helper  functions  prototypes ******************/
/* that is, not visible outside this file */
static char* normalize_word(char* word);

/***************************** global functions *********************************/
/* that is, visible outside this file */

void create_sudoku(puzzle_t* puzzle, char* level);
void build_full_sudoku(puzzle_t* puzzle, char* level);

/******************************* sudoku_create() ********************************/
/* see create.h for description */

void build_full_sudoku(puzzle_t* puzzle, char* level) {
    srand (time(NULL));
    int random_num;

    // ensures we start with empty entries -> 0
    for (int i = 0; i < get_grid_size(puzzle); i++) {       
        for (int j = 0; j < get_grid_size(puzzle); j++) {   
            set_box_value(puzzle, 0, i, j);
        } 
    } 

    if (strcmp(level, "hard")==0 || strcmp(level, "easy")==0) {
        // the min_main_diagonal line boxes is independent, fill it first
        for (int i = 0; i < get_grid_size(puzzle); i++) {       // rows
            do { 
                
                random_num = (rand() % get_grid_size(puzzle)) + 1; //from (1-9)
            } 
            // while you can't add that value in, change the number
            while (!val_not_in_cross_section(puzzle, i, i, random_num, level));

            // add the value to the grid
            set_box_value (puzzle, random_num, i,i);
        }
    }
    
    // fill 3x3 boxes  in main duagonal (min 27 entries)
    for (int min_main_diag = 0; min_main_diag < get_grid_size(puzzle); min_main_diag += sqrt((double)get_grid_size(puzzle))) {
    
        for (int i = 0; i < sqrt((double)get_grid_size(puzzle)); i++) {       // rows
            for (int j = 0; j < sqrt((double)get_grid_size(puzzle)); j++) {   // columns 
                if (get_grid(puzzle)[min_main_diag + i][min_main_diag + j] == 0) {
                    do { 
                        
                        random_num = (rand() % get_grid_size(puzzle)) + 1; //from (1-9)
                    } 
                    // change number if can't be aded in specific box
                    while (!is_val_in_box(puzzle, min_main_diag, min_main_diag + i, min_main_diag + j, random_num, level));

                    // add the value to the grid
                    get_grid(puzzle)[min_main_diag + i][min_main_diag + j] = random_num;
                }
            } 
        } 
    }

    // re-build if not solvable
    if (!solve_sudoku(puzzle,0,0, level)) {
        build_full_sudoku(puzzle, level);
    }
}





/*********************** create_sudoku() ******************************/
void
create_sudoku(puzzle_t* puzzle, char* level){
    
    if(puzzle == NULL) return ;
    // initialize non- seed randomization
    srand(time(NULL));
    
    // nomalize dificulty level 
    normalize_word(level);
    //printf("mmmmmmmmmmm   %d\n", get_num_todelete(puzzle, level));

    ///////////////////////////////////////////////
    // delete 44 box_values if num_to_delete == 44, 56 if num_to_delete == 56
    for(int i = 0; i <  get_num_todelete(puzzle, level); i++){
      
        int x_todelete; // x postion of random box to delete
        int y_todelete; // y postion of random box to delete

        // check if solution of puzzle would be unique if val at x_todelete, y_todelete is actually deleted
        bool is_unique_solution = true;
        do{
            
            do{
                // pick a random x to delete
                x_todelete = rand() % get_grid_size(puzzle); // from 0 to 8

                //pick a random y
                y_todelete = rand() % get_grid_size(puzzle); // from 0 to 8      
            }
            // check if the box at that location has already been deleted
            // while we haven't found one that has  not been deleted already , keep picking random x,y.
            while(get_box_value(puzzle, x_todelete, y_todelete) == 0);

            // once we find one(not deleted), remember it and see if solution the sudoku would have while that value is deleted is unique
            int to_delete_value = get_box_value(puzzle, x_todelete, y_todelete);

            // delete value 
            set_box_value(puzzle, 0, x_todelete, y_todelete);

            //and check that solution produced is unique
            is_unique_solution = (count_num_solutions(puzzle, level) == 1);

            // if solution is not unique, put it back
            if(!is_unique_solution){
                
                set_box_value(puzzle, to_delete_value, x_todelete, y_todelete);
            }
            // if solution is unique
            else{
                is_unique_solution = true; // continue to next deletion
            }
        }
        while(!is_unique_solution);
   }
} 


/******************************************************************************************/
/***************** static    helper   methods   defined   here   **************************/
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
    if(word == NULL) return NULL;

    for(int i = 0; i <= (strlen(word)); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}


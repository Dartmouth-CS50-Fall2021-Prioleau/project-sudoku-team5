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

/******************* static helper methods **********************/
static int count_num_solutions_helper(puzzle_t* puzzle, char*level, int num_solutions, int init_row, int init_column);

/************************ global fucntions *********************/
int count_num_solutions(puzzle_t* puzzle, char* level);
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value, char* level);


/********************** count_num_solutions() *************************/
/*
 *
 *
 * 
 * 
 * 
 */
int count_num_solutions(puzzle_t* puzzle, char* level) 
{   
    // call solution counter
    return count_num_solutions_helper(puzzle,level, 0, 0, 0);
}



/********************** count_num_solutions_helper() *************************/
/*
 *
 *
 * 
 * 
 * 
 */
static int count_num_solutions_helper(puzzle_t* puzzle, char*level, int num_solutions, int init_row, int init_column)
{
    //check what rows boxs have been seen already -> bases case
    if(init_row == get_grid_size(puzzle) && init_column == get_grid_size(puzzle)) return num_solutions+1; // if  init_row init_columns are at the end, we've visited all.

    // visit all boxes not yet seen left to right top to bottom
    for(int i= init_row; i < get_grid_size(puzzle); i++)
    {
        int j = (i == init_row) ? init_column : 0;

        for( ; j < get_grid_size(puzzle); j++)
        {
            // check if the value of the box  at that location is empty
            if(get_box_value(puzzle, i, j) == 0)
            {    
                for(int value=1; value<=get_grid_size(puzzle); value++)
                {
                    // check that value of sudoku is a valid possible value of box 
                    if(val_not_in_cross_section(puzzle, i, j, value, level))
                    {    
                        
                        set_value(get_box_from_grid(puzzle,i , j), value);

                        // count_num of solution of that sub sudoku with new value
                        if(j == get_grid_size(puzzle)-1){
                            num_solutions = count_num_solutions_helper(puzzle, level, num_solutions, i+1, 0);
                        }else
                        {
                             num_solutions = count_num_solutions_helper(puzzle, level, num_solutions, i, j+1);
                        }
                        set_value(get_box_from_grid(puzzle, i, j), 0);
                    }

                }// some entries did not work so unsolvable
                return num_solutions;
            }
        }

    }return num_solutions +1;

}



/**************************************   val_not_in_cross_section() ************************************/
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value, char* level)
{
    // iterate over rows to check their columns

    for(int r = 0; r <get_grid_size(puzzle); r++){
        if((get_box_value(puzzle, r, column) == value) && r !=row){
            return false;
        }
    }

    // iterate over columns to check their rows
    for(int c = 0; c < get_grid_size(puzzle); c++){
        if((get_box_value(puzzle, row, c) == value) && c != column){
            return false;
        }
    }

    // check box

    // Check box
    int rbox = row/sqrt((double)get_grid_size(puzzle));
    int cbox = column/sqrt((double)get_grid_size(puzzle));
    for (int i = rbox*sqrt((double)get_grid_size(puzzle)); i < (rbox*sqrt((double)get_grid_size(puzzle)))+sqrt((double)get_grid_size(puzzle)); i++) {
        for (int j = cbox*sqrt((double)get_grid_size(puzzle)); j < (cbox*sqrt((double)get_grid_size(puzzle)))+sqrt((double)get_grid_size(puzzle)); j++) {
            if ((get_box_value(puzzle, i, j) == value) && i != row && j != column   ) {
                return false;
            }
        }
    }

    // diagonal sudoku
    if (strcmp(level, "easy") == 0 || strcmp(level, "hard" )  == 0) {
        // the negative sloped diagonal
        if (row == column) {
            for (int i = 0; i < get_grid_size(puzzle); i++) {
                // check if it's in the value
                if (i != row && (get_box_value(puzzle, i, i) ==value) ) {
                    return false;
                }
            }
        }
        // the positive sloped diagonal
        if (get_grid_size(puzzle)-1-row == column) {
            for (int i = 0; i < get_grid_size(puzzle); i++) {
                // check if it's in the value
                if (get_grid_size(puzzle)-1-i != row && column != i && (get_box_value(puzzle, get_grid_size(puzzle)-1-i, i) == value)) {
                    return false;
                }
            }
        }
    }
    return true;

}



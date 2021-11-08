#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "../solve/solve.h"
#include "../library/counters.h"
#include "../box/box.h"
#include "../puzzle/puzzle.h"


static int count_num_solutions_helper(box_t* sudoku[9][9], char*level, int num_solutions, int init_row, int init_column);
bool val_not_in_cross_section(box_t* sudoku[9][9], int row, int column, int value, char* level);


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
                        set_value(sudoku[i][j], 0);
                    }

                }// some entries did not work so unsolvable
                return num_solutions;
            }
        }

    }return num_solutions +1;

}



/**************************************   val_not_in_cross_section() ************************************/
bool val_not_in_cross_section(box_t* sudoku[9][9], int row, int column, int value, char* level)
{

    // iterate over rows to check their columns

    for(int r = 0; r < 9; r++){
        if((get_value(sudoku[r][column]) == value ) && r !=row){
            return false;
        }
    }

    // iterate over columns to check their rows
    for(int c = 0; c < 9; c++){
        if((get_value(sudoku[row][c]) == value) && c != column){
            return false;
        }
    }

    // check box

    // Check box
    int rbox = row/3;
    int cbox = column/3;
    for (int i = rbox*3; i < (rbox*3)+3; i++) {
        for (int j = cbox*3; j < (cbox*3)+3; j++) {
            if (   (get_value(sudoku[i][j]) == value) && i != row && j != column   ) {
                return false;
            }
        }
    }

    // diagonal sudoku
    if (strcmp(level, "easy") == 0) {
        // the negative sloped diagonal
        if (row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the value
                if (i != row && (get_value(sudoku[i][i]) == value)    ) {
                    return false;
                }
            }
        }
        // the positive sloped diagonal
        if (8-row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the value
                if (8-i != row && column != i && (get_value(sudoku[8-i][i]) == value)) {
                    return false;
                }
            }
        }
    }



    // diagonal sudoku
    if (strcmp(level, "hard")  == 0){
        // the negative sloped diagonal
        if (row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the value
                if (i != row && (get_value(sudoku[i][i]) == value)) {
                    return false;
                }
            }
        }
        // the positive sloped diagonal
        if (8-row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the value
                if (8-i != row && column != i && (get_value(sudoku[8-i][i]) == value)) {
                    return false;
                }
            }
        }
    }

    return true;

}














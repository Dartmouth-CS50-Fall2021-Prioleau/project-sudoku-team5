#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "solve.h"
#include "../puzzle/puzzle.h"
#include "../create/create.h"


/******************* static helper methods **********************/
static int count_num_solutions_helper(puzzle_t* puzzle, char*level, int num_solutions, int init_row, int init_column);

/************************ global functions *********************/
/* that is, visible outside this file */
bool solve_sudoku(puzzle_t* puzzle, int row, int column, char* level);
int count_num_solutions(puzzle_t* puzzle, char* level);


/*********************** solve_sudoku() ******************************/
/* see  solve.h for description*/
bool solve_sudoku(puzzle_t* puzzle, int row, int column, char* level){
    // check if all entries have been visited
    if (row == get_grid_size(puzzle) && column == 0) {
        return true;
    }
    // Visit squares that have not yet been visited, from left to right
    for (int i=row; i< get_grid_size(puzzle); i++) {
        int j =(i == row) ? column : 0;
         
        for ( ; j<get_grid_size(puzzle); j++) {
            // check if entry is empty
            if (get_box_value(puzzle, i, j) == 0) {

                // Try every valid number for this entry
                int possibilities[get_grid_size(puzzle)] ; //{1, 2, 3, 4, 5, 6, 7, 8, 9};
                for(int i=1 ; i<=get_grid_size(puzzle);i++) {
                  possibilities[i-1] = i;
                }

                int count = 0; 

                while (count < get_grid_size(puzzle)) {
                    int random_possibility = (rand() % get_grid_size(puzzle)) + 1; 
                    if (possibilities[random_possibility - 1] != 0 ) {
                        if (val_not_in_cross_section(puzzle, i, j, random_possibility)) {
                            set_box_value(puzzle, random_possibility, i, j);

                            // recurse with new sudoku -> move to next entry
                            bool is_sub_solvable;
                            if (j == get_grid_size(puzzle)-1) {
                                is_sub_solvable = solve_sudoku(puzzle, i+1, 0, level);
                            }
                            else {
                                is_sub_solvable = solve_sudoku(puzzle, i, j+1, level);
                            }

                            if (is_sub_solvable) {              // found a solution that works
                                return true;
                            }
                            else {    // solution didn't work
                                set_box_value(puzzle,0, i, j);
                            }
                        }
                        possibilities[random_possibility - 1] = 0; 
                        count ++; 
                    }
                }
                // Some entry did not work, so this is unsolvable
                return false;
            }
        }
    }
    return true;
}




/********************** count_num_solutions() *************************/
/* see  solve.h for description */
int count_num_solutions(puzzle_t* puzzle, char* level) {   
    // call helper solution counter
    return count_num_solutions_helper(puzzle,level, 0, 0, 0);
}


/******************************************************************************************/
/***************** static    helper   methods   defined   here   **************************/
/******************************************************************************************/
/* that is, not visible outside this file */

/********************** count_num_solutions_helper() *************************/
/* Counts the number of sultions using recursion and backtracking.
 * Returns number of solutions  for the given puzzle to caller.
 * Caller provides tvalid puzzle, the level, the rows to start 
 * recursing from, and the number of solutions so far.
 * 
 */
static int 
count_num_solutions_helper(puzzle_t* puzzle, char*level, int num_solutions, int init_row, int init_column)
{
    //check what rows boxs have been seen already -> bases case
    if(init_row == get_grid_size(puzzle) && init_column == get_grid_size(puzzle)) return num_solutions+1; // if  init_row init_columns are at the end, we've visited all.

    // visit all boxes not yet seen left to right top to bottom
    for(int i = init_row; i < get_grid_size(puzzle); i++)
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
                    if(val_not_in_cross_section(puzzle, i, j, value))
                    {    
                        
                        set_box_value(puzzle, value, i ,j);

                        // count_num of solution of that sub sudoku with new value
                        if(j == get_grid_size(puzzle)-1){
                            num_solutions = count_num_solutions_helper(puzzle, level, num_solutions, i+1, 0);
                        }else
                        {
                             num_solutions = count_num_solutions_helper(puzzle, level, num_solutions, i, j+1);
                        }
                        set_box_value(puzzle, 0,i, j);
                    }

                }// some entries did not work so unsolvable
                return num_solutions;
            }
        }

    }return num_solutions +1;

}




































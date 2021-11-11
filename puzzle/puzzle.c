#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../library/memory.h"
#include <string.h>

/**************** file-local global variables ****************/
/* none */


/**************** global types ****************/
typedef struct puzzle {
    int size;
    int** grid;
}  puzzle_t;

puzzle_t* puzzle_new(int size) {

    puzzle_t* puzzle = count_malloc((sizeof(puzzle_t)));
    if (puzzle != NULL) {
        puzzle->size = size;
        double sqrt_size = sqrt(size);
        if ((ceil(sqrt_size) == floor(sqrt_size)) && size > 0) {  // check for perfect square
            int** grid = count_calloc_assert(size, sizeof(int*), "GRID IS NULL OH NO\n");
            if (grid != NULL) {
                puzzle->grid = grid;
                for (int i = 0; i < size; i++) {
                    int* row_holder = count_calloc_assert(size, sizeof(int), "ROW-HOLDER IS NULL OH NO\n");
                    grid[i] = row_holder;
                    for (int j = 0; j < size; j++) {  // needs to be revised
                        grid[i][j] = 0;
                    }
                }  
                return puzzle;
            }
        }
        return NULL;
    }
    return NULL;
}

int get_grid_size(puzzle_t* puzzle)
{
    if (puzzle != NULL && puzzle->grid != NULL) {
        return puzzle->size;
    }
    return -1;
}

int get_box_val_from_grid(puzzle_t* puzzle, int x, int y) {

   // if ((puzzle != NULL && puzzle->grid != NULL) && ((x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size))) {
        //box_t* grid[9][9] = puzzle->grid;
        int box = puzzle->grid[x][y];
        return box;
   // }
    return -1;
}

bool set_box_val_in_grid(puzzle_t* puzzle, int x, int y, int box)
{
   // if (puzzle != NULL && puzzle->grid != NULL && (box > 0 && box <= puzzle->size) && (x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size)) {
        puzzle->grid[x][y] = box;
        //return puzzle->grid[x][y];
   // }
    return true;
}

/**************************************   val_not_in_cross_section() ************************************/
bool val_not_in_cross_section_2(puzzle_t* puzzle, int x, int y, int value, char* level)
{
    // iterate over rows to check their columns
    for(int r = 0; r < puzzle->size; r++){
        if(((get_box_val_from_grid(puzzle, r, y)) == value) && r != x){
            return false;
        }
    }

    // iterate over columns to check their rows
    for(int c = 0; c < puzzle->size; c++){
        if(((get_box_val_from_grid(puzzle, x, c)) == value) && c != y){
            return false;
        }
    }

    int sqrt_size = sqrt(puzzle->size);
    int rbox = -(x % sqrt_size);
    int cbox = -(y % sqrt_size);

    // check box
    for (int i = rbox; i < (sqrt_size + rbox); i++) {
        for (int j = cbox; j < (sqrt_size + cbox); j++) {
            if ((x + i != x) || (y + j != y)) {
                int neighbor_x = x + i;
                int neighbor_y = y + j;
                if ((get_box_val_from_grid(puzzle, neighbor_x, neighbor_y) == value)) {
                    return false;
                }
            }
        }
    }

    // diagonal sudoku
    if (strcmp(level, "easy") == 0 || strcmp(level, "hard") == 0) {
        // the negative sloped diagonal
        if (x == y) {
            for (int i = 0; i < puzzle->size; i++) {
                // check if it's in the value
                if (i != x && (get_box_val_from_grid(puzzle, i, i) == value)    ) {
                    return false;
                }
            }
        }
        // the positive sloped diagonal
        int neg_diag = puzzle->size - 1;
        if ((neg_diag - x) == y) {
            for (int i = 0; i < puzzle->size; i++) {
                // check if it's in the value
                if (((neg_diag - i) != x) && (y != i) && (get_box_val_from_grid(puzzle, (neg_diag - i), i) == value)) {
                    return false;
                }
            }
        }
    }
    return true;
}

void puzzle_delete(puzzle_t* puzzle)
{
    if (puzzle->grid != NULL) {
        for (int i = 0; i < puzzle->size; i++) {
            if (puzzle->grid[i] != NULL) {
                count_free(puzzle->grid[i]);
            }
        }
        count_free(puzzle->grid);
    }
    
    
    if (puzzle != NULL) {
        count_free(puzzle);
    }
}

/*****************************************/
/************Printing Methods*************/
/*****************************************/

void puzzle_print_simple (puzzle_t* puzzle, FILE* fp)
{
   for( int i = 0; i < puzzle->size; i++) {  // row
      for(int j= 0; j < puzzle->size; j++) {  // column
        int val = puzzle->grid[i][j];
        printf("%d ", val);
      }
      printf("\n");
   }
    // handle NULL sudoku
    /*
    if(fp != NULL) { 
        if(puzzle == NULL || puzzle->grid == NULL){
            printf("(null)\n");
        } else {
            for( int i = 0; i < puzzle->size; i++) {  // row
                for(int j= 0; j < puzzle->size; j++) {  // column
                    fprintf(fp, "%d ", puzzle->grid[i][j]);
                }
                printf("\n"); // print next row of sudoku
            }
        }
    }
    */
}

void puzzle_print_formated(puzzle_t* puzzle, FILE* fp) 
{
    if (fp != NULL) {
        if (puzzle != NULL && puzzle->grid != NULL) {
            
            
            fprintf(fp, "+" );
        } else {
            fprintf(fp, "(null)\n" );
            
        }
    }
}

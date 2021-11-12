/*
 * puzzle.c - CS50 'puzzle' module
 *
 * see puzzle.h for more information
 * 
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <math.h>
#include "puzzle.h"
#include "../library/memory.h"
#include "../library/file.h"
#include "../solve/solve.h"
#include "../create/create.h"



/**************** file-local global variables ****************/
/* none */

/*********************** local types ************************/
/* none */

/********************** global types *************************/
typedef struct puzzle {
    int size;     // size of puzzle
    int** grid;   // 2-D array of integers
} puzzle_t;

/*********************** local functions  **********************/
/* that is, not visible outside this file */
/* none */

/*********************** global functions **********************/
/* that is, visible outside this file */
puzzle_t* puzzle_new(int size);
int** get_grid(puzzle_t* puzzle);
int get_grid_size(puzzle_t* puzzle);
int get_box_value(puzzle_t* puzzle, int x, int y);
bool set_box_value(puzzle_t* puzzle, int value, int x, int y);
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value);
void puzzle_delete(puzzle_t* puzzle);
void puzzle_print_simple (FILE* fp, puzzle_t* puzzle);
void puzzle_print_formated (FILE* fp, puzzle_t* puzzle);
bool is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry);
bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle);
void print_box_value( FILE* fp, puzzle_t* puzzle, int box_value);

/*********************** puzzle_new() ************************/
/* see  puzzle.h for description*/
puzzle_t* puzzle_new(int size) {

    puzzle_t* puzzle = count_malloc((sizeof(puzzle_t))); // allocate memory for puzzle on heap

    if (puzzle != NULL)
     {
        puzzle->size = size;
        double sqrt_size = sqrt(size);

        if ((ceil(sqrt_size) == floor(sqrt_size)) && size > 0) // check for perfect square
        {  
            int** grid = count_calloc_assert(size, sizeof(int**), "GRID IS NULL OH NO\n");
            if (grid != NULL){
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



/********************* get_grid() *********************/
/* see  puzzle.h for description*/
int** 
get_grid(puzzle_t* puzzle){
    if(puzzle !=NULL){
        return puzzle->grid;
    }
    return NULL;
}

/***************************  get_grid_size() *****************/
/* see  puzzle.h for description*/
int
get_grid_size(puzzle_t* puzzle)
{
    if (puzzle != NULL && puzzle->grid != NULL) {
        return puzzle->size;
    }
    return -1;
}


/***************************  get_box_value() *****************/
/* see  puzzle.h for description*/
int 
get_box_value(puzzle_t* puzzle, int x, int y)
{
    if ((puzzle != NULL && puzzle->grid != NULL) && ((x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size))) {
        int box_value = puzzle->grid[x][y];
        return box_value;
    }
    return -1;
}


/***************************  set_box_value() *****************/
/* see  puzzle.h for description*/
bool
set_box_value(puzzle_t* puzzle, int value, int x, int y)
{
    if (puzzle != NULL && puzzle->grid != NULL && (value> -1 && value <= puzzle->size) && (x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size)) {
        puzzle->grid[x][y] = value;
        return true;
    }
    return false;
}


void print_box_value( FILE* fp, puzzle_t* puzzle, int box_value){

    if (fp != NULL){
        if (puzzle->size <= 9) {
            fprintf(fp, "%d ", box_value); //print  box's value
        } else {

        }
            
    }
}



/**************************************  val_not_in_cross_section() ************************************/
/* see  puzzle.h for description*/

/**************************************   val_not_in_cross_section() ************************************/
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value)
{
    // iterate over rows to check their columns
    int size = puzzle->size;

    for(int r = 0; r < size; r++){
        if((get_box_value(puzzle, r, column) == value) && r !=row){
            return false;
        }
    }

    // iterate over columns to check their rows
    for(int c = 0; c < size; c++){
        if((get_box_value(puzzle, row, c) == value) && c != column){
            return false;
        }
    }

    // Check box
    int sqrt_grid_size = sqrt((double)size);
    int rbox = row/sqrt_grid_size;
    int cbox = column/sqrt_grid_size;
    for (int i = rbox*sqrt_grid_size; i < ((rbox*sqrt_grid_size)+sqrt_grid_size); i++) {
        for (int j = cbox*sqrt_grid_size; j < (cbox*sqrt_grid_size)+sqrt_grid_size; j++) {
            if ( i != row && j != column && (get_box_value(puzzle, i, j) == value) ) {
                return false;
            }
        }
    }

    // diagonal sudoku
    //if (strcmp(level, "easy") == 0 || strcmp(level, "hard" )  == 0) {
        // the negative sloped diagonal
    if (row == column) {
        for (int i = 0; i < size; i++) {
            // check if it's in the value
            if (i != row && (get_box_value(puzzle, i, i) ==value) ) {
                return false;
            }
        }
    }

    int largest_coord = size-1;
    // the positive sloped diagonal
    if (largest_coord-row == column) {
        for (int i = 0; i < size; i++) {
            // check if it's in the value
            if (largest_coord-i != row && column != i && (get_box_value(puzzle, largest_coord-i, i) == value)) {
                return false;
            }
        }
    }
    //}
    return true;

}






/********************* puzzle_delete() *****************/
/* see  puzzle.h for description*/
void
puzzle_delete(puzzle_t* puzzle)
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



/*************************  puzzle_print_simple() ********************/
/* see  puzzle.h for description*/
void 
puzzle_print_simple(FILE* fp, puzzle_t* puzzle)
{
    // handle NULL sudoku
    if(fp != NULL) {
        if (puzzle == NULL || puzzle->grid == NULL) {
            fprintf(fp, "\n(null)\n");
        } else {
            for( int i = 0; i < puzzle->size; i++){  // row
                for(int j= 0 ; j < puzzle->size; j++){  // column
                    print_box_value(fp, puzzle, puzzle->grid[i][j]); 
                }
                fprintf(fp, "\n"); // print next row of puzzle
            }
            fprintf(fp, "\n");
            
        }
    } else {
        fprintf(fp, "could not open file to write :( \n\n");
    }

    

}

// void
// puzzle_print_simple (FILE* fp, puzzle_t* puzzle)
// {
//     // handle NULL sudoku
//     if(fp != NULL) { 
//         if(puzzle == NULL || puzzle->grid == NULL){
//             printf("(null)\n");
//         } else {
//             for( int i = 0; i < puzzle->size; i++) {  // row
//                 for(int j= 0; j < puzzle->size; j++) {  // column
//                     fprintf("%d\t", puzzle->grid[i][j], fp);
//                 }
//                 printf("\n"); // print next row of sudoku
//             }
//         }
//     }
// }


/*************************  puzzle_print_formated() ********************/
/* see  puzzle.h for description*/
void 
puzzle_print_formated (FILE* fp, puzzle_t* puzzle)
{
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(puzzle == NULL){
        fprintf(fp, "(null)");
        return;
    }


    printf("+-------+-------+-------+\n");
     
    // the  3 3X3 sudoku's in the first row
    for ( int i = 0; i< 3; i++){  //first three rows

        for(int j= 0 ;j < 9; j++){ // all their collumns

            // start of column
            if(  j == 0 ){
                printf("| ");
                print_box_value(fp, puzzle, puzzle->grid[i][j]);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle, puzzle->grid[i][j]);
                 printf("| ");
             }
             else if ( j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle, puzzle->grid[i][j]);
                 printf("|");
             }
            else{
                print_box_value(fp, puzzle, puzzle->grid[i][j]); 
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");


    // the  3 3X3 sudoku's in the second row
    for ( int i = 3; i< 6; i++){

        for(int j= 0 ;j < 9; j++){

            // start of column
            if(  j == 0 ){
                printf("| ");
                print_box_value(fp, puzzle, puzzle->grid[i][j]);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle, puzzle->grid[i][j]);
                 printf("| ");
             }
            else{
                print_box_value(fp, puzzle, puzzle->grid[i][j]);
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");



    // the  3 3X3 sudoku's in the third(last) row
    for ( int i = 6; i< 9; i++){  // last three rows

        for(int j= 0 ;j < 9; j++){ // all their columns

            // start of column
            if(  j == 0 ){
                printf("| ");
                print_box_value(fp, puzzle, puzzle->grid[i][j]);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle, puzzle->grid[i][j]);
                 printf("| ");
             }
            else{
                print_box_value(fp, puzzle, puzzle->grid[i][j]);
            }
        }printf("\n"); // print next row of sudoku     
    } printf("+-------+-------+-------+\n"); // of sudoku line
}



/**************************  is_val_in_box() ***************************/
/* see puzzle.h for description */
bool 
is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry) {
    // if the entry is already in the 3x3 box
    int sqrt_size = sqrt(puzzle->size); 
    for (int i = 0; i < sqrt_size; i++) {
        for (int j = 0; j < sqrt_size; j++) {
            if (get_grid(puzzle)[diag+i][diag+j] == entry) {
                return false;
            }
        } 
    }
    
    return true;
}





/**************************** bool parse_user_puzzle() **********************************/
/* see puzzle.h for description */
bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle)
{ 
  // return NULL if either fp or sudoku is NULL
  if (fp == NULL || puzzle == NULL ){
    printf("something is wrong\n");
    return false;
  }
  int puzzle_size = puzzle->size;
  // scan all sudoku entries and check if they were successfully mathced and assigned
  for (int r = 0; r < puzzle_size; r++) 
  {
    for (int c = 0; c < puzzle_size; c++)
    {
      int value; // store scanned value here

      // check value was successfully matched and assigned
      int scan_status;
      do {
        char* num = freadwordp(fp);

        //Check if the user input less than 81 numbers
        if (num == NULL) {
          return false;
        }
        scan_status = sscanf(num, "%d", &value);

        free(num);
      }  
       
      while(scan_status != 1); 

      // ensure that value is between 0 andf 9 strictly
      if(value <= get_grid_size(puzzle) && value >= 0)
      {
        //create a new box and set its value to be the scanned value, and put it in the sudoku 
        set_box_value(puzzle, value, r, c);
      }
      else return false;
    }
      
  } 
  
  // check the user didn't input more than 81 numbers
    char* num;
    
    while ((num = freadwordp(fp)) != NULL ) {
      if(isdigit(num[0])) {
          return false;
      }
      free(num);
    }
    
  return true; 
}
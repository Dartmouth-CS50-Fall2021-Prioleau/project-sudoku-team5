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
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value, char* level);
void puzzle_delete(puzzle_t* puzzle);
void puzzle_print_simple (FILE* fp, puzzle_t* puzzle);
void puzzle_print_formated (FILE* fp, puzzle_t* puzzle);
bool is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry, char* level);
bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle);
void print_box_value( FILE* fp, int box_value);

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


void print_box_value( FILE* fp, int box_value){

    if (fp != NULL){
          printf("%d ", box_value); //print  box's value
    }
}



/**************************************  val_not_in_cross_section() ************************************/
/* see  puzzle.h for description*/

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
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(puzzle->grid == NULL){
        printf("(null)");
        return;
    }

    for( int i = 0; i < puzzle->size; i++){  // row
        for(int j= 0 ; j < puzzle->size; j++){  // column
           print_box_value(fp, puzzle->grid[i][j]); 
        }
        printf("\n"); // print next row of puzzle
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
                print_box_value(fp,puzzle->grid[i][j]);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle->grid[i][j]);
                 printf("| ");
             }
             else if ( j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle->grid[i][j]);
                 printf("|");
             }
            else{
                print_box_value(fp, puzzle->grid[i][j]); 
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");


    // the  3 3X3 sudoku's in the second row
    for ( int i = 3; i< 6; i++){

        for(int j= 0 ;j < 9; j++){

            // start of column
            if(  j == 0 ){
                printf("| ");
                print_box_value(fp, puzzle->grid[i][j]);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle->grid[i][j]);
                 printf("| ");
             }
            else{
                print_box_value(fp, puzzle->grid[i][j]);
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");



    // the  3 3X3 sudoku's in the third(last) row
    for ( int i = 6; i< 9; i++){  // last three rows

        for(int j= 0 ;j < 9; j++){ // all their columns

            // start of column
            if(  j == 0 ){
                printf("| ");
                print_box_value(fp, puzzle->grid[i][j]);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 print_box_value(fp, puzzle->grid[i][j]);
                 printf("| ");
             }
            else{
                print_box_value(fp, puzzle->grid[i][j]);
            }
        }printf("\n"); // print next row of sudoku     
    } printf("+-------+-------+-------+\n"); // of sudoku line
}



/**************************  is_val_in_box() ***************************/
/* see puzzle.h for description */
bool 
is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry, char* level) {
    // // check if that box is not already filled
    // if (get_grid(puzzle)[row][column] != 0) {
    //     return false; 
    // }
    
    // if the entry is already in the 3x3 box 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (get_grid(puzzle)[diag+i][diag+j] == entry) {
                return false;
            }
        } 
    }
    // // diagonal sudoku
    // if (strcmp(level, "hard")==0 || strcmp(level, "easy")==0) {
    //     // the negative sloped diagonal
    //     if (row == column) {
    //         for (int i = 0; i < 9; i++) {
    //             // check if it's in the entry
    //             if (i != row && get_grid(puzzle)[i][i] == entry) {
    //                 return false;
    //             }
    //         }
    //     }
    // }
    // if it was not in the box
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
  
  // scan all sudoku entries and check if they were successfully mathced and assigned
  for (int r = 0; r < 9; r++) 
  {
    for (int c = 0; c < 9; c++)
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


/***************************  is_valid_unsolved() *****************/
/* see  puzzle.h for description*/
bool is_valid_unsolved(puzzle_t* puzzle) {

  int count = 0;

  for(int i = 0; i < puzzle->size; i ++) {
    for(int j = 0; j < puzzle->size; j ++) {
      if(puzzle->grid[i][j] != 0) {
        count += 1; 
        if(!val_not_in_cross_section(puzzle, i, j, puzzle->grid[i][j], "easy")) {
          return false;
        }
      }
    }

  }

  if(count >= 25) {
    return true;

  }
  else {
    return false;
  }

}
/***************************  is_valid_solved() *****************/
/* see  puzzle.h for description*/
bool is_valid_solved(puzzle_t* puzzle) {


  for(int i = 0; i < puzzle->size; i ++) {
    for(int j = 0; j < puzzle->size; j ++) {
      
      if(puzzle->grid[i][j] == 0) {
        return false;
      }

      if(!val_not_in_cross_section(puzzle, i, j, puzzle->grid[i][j], "easy")) {
        return false;
      }

      }
    }

  return true;

}
/*
 * puzzle.c - CS50 Sudoku Final Project 'puzzle' module
 * 
 * Authors: Veronica Quidore, Dylan Bienstock, Salifyanji J. Namwila
 * see puzzle.h for more information
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
void fancy_horz_border_helper(FILE* fp, int border_box_size, int sqrt_size);

/*********************** global functions **********************/
/* that is, visible outside this file */
puzzle_t* puzzle_new(int size);
int** get_grid(puzzle_t* puzzle);
int get_grid_size(puzzle_t* puzzle);
int get_box_value(puzzle_t* puzzle, int x, int y);
bool set_box_value(puzzle_t* puzzle, int value, int x, int y);
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value);
void puzzle_delete(puzzle_t* puzzle);
int get_num_todelete(puzzle_t* puzzle, char*level);
void puzzle_print_simple (FILE* fp, puzzle_t* puzzle);
void puzzle_print_formated (FILE* fp, puzzle_t* puzzle);
bool is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry);
bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle);
void print_box_value( FILE* fp, puzzle_t* puzzle, int box_value);



/*********************** puzzle_new() ************************/
/* see  puzzle.h for description*/
puzzle_t* puzzle_new(int size) {

    double sqrt_size = sqrt(size);

    if ((ceil(sqrt_size) == floor(sqrt_size)) && size > 0 && size < 100) // check for perfect square and 0 < size < 100
    {
        puzzle_t* puzzle = count_malloc((sizeof(puzzle_t))); // allocate memory for puzzle on heap

        if (puzzle != NULL)
        {
            puzzle->size = size;
            
            int** grid = count_calloc_assert(size, sizeof(int**), "GRID IS NULL OH NO\n"); // holds second dimension
            if (grid != NULL){
                puzzle->grid = grid;
                for (int i = 0; i < size; i++) {
                    int* row_holder = count_calloc_assert(size, sizeof(int), "ROW-HOLDER IS NULL OH NO\n");  // for 2-D array
                    grid[i] = row_holder;
                    for (int j = 0; j < size; j++) {  // needs to be revised
                        grid[i][j] = 0;  // initialize every coordinate in the grid to null
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
        return puzzle->grid; // int** pointer
    }
    return NULL;
}

/***************************  get_grid_size() *****************/
/* see  puzzle.h for description*/
int
get_grid_size(puzzle_t* puzzle)
{
    if (puzzle != NULL && puzzle->grid != NULL) {
        return puzzle->size;    //int size
    }
    return -1;
}


/***************************  get_box_value() *****************/
/* see  puzzle.h for description*/
int 
get_box_value(puzzle_t* puzzle, int x, int y)
{
    // must be non-NULL puzzle and valid x and y coordinates
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
    // must be non-NULL puzzle, valid x and y coordinates, and valid value (>= 0)
    if (puzzle != NULL && puzzle->grid != NULL && (value > -1 && value <= puzzle->size) && (x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size)) {
        puzzle->grid[x][y] = value;
        return true;
    }
    return false;
}


void print_box_value( FILE* fp, puzzle_t* puzzle, int box_value){

    if (fp != NULL){
        if (puzzle->size <= 9) { // single digit
            fprintf(fp, "%d ", box_value); //print  box's value
        } else { // double digit
            fprintf(fp, "%02d ", box_value);
        }
            
    }
}

/************************* get_num_todelete()  *********************/
int get_num_todelete(puzzle_t* puzzle, char*level){

    if (puzzle != NULL){

        if(puzzle-> size == 9) // set number to delete for 9x9
        {
            if (strcmp(level, "easy") == 0) return 44;
            else if(strcmp(level, "hard") == 0) return 56;
        }
        else{ // determine proportional percentage to delete depending on level
            if (strcmp(level, "easy") == 0) {
                 int num = 0.2* pow(puzzle-> size,2);
                 return num ;
            }
            else if(strcmp(level, "hard") == 0){
               int num = 0.25* pow(puzzle-> size,2) ;
               return num;
            } 
        }    
    }
    return -1;
}


/**************************************  val_not_in_cross_section() ************************************/
/* see  puzzle.h for description*/
bool 
val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value)
{
    // iterate over rows to check their columns
    if (puzzle != NULL) {
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

        // Check box, starting in upper left corner and iterating to bottom right corner
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

        // diagonal sudoku slopes

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

        return true;  // value not in cross section

    } else {
        return true;
    }
    
}


/********************* puzzle_delete() *****************/
/* see  puzzle.h for description*/
void
puzzle_delete(puzzle_t* puzzle)
{
    if (puzzle->grid != NULL) {
        for (int i = 0; i < puzzle->size; i++) {
            if (puzzle->grid[i] != NULL) {
                count_free(puzzle->grid[i]); // free each column
            }
        }
        count_free(puzzle->grid); // free row containing columns (c-style memory allocation)
    }
    
    if (puzzle != NULL) {
        count_free(puzzle);  // free struct
    }
}

/*************************  puzzle_print_simple() ********************/
/* see  puzzle.h for description*/
void 
puzzle_print_simple(FILE* fp, puzzle_t* puzzle)
{
    // handle NULL sudoku
    if(fp != NULL) {
        if (puzzle == NULL || puzzle->grid == NULL) { // null grid
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
        fprintf(stderr, "could not open file to write :( \n\n");
    }
}

/*************************  puzzle_print_formated() ********************/
/* see  puzzle.h for description*/
void 
puzzle_print_formated (FILE* fp, puzzle_t* puzzle)
{
    if (fp != NULL) {
        if (puzzle != NULL && puzzle->grid != NULL) {
            if (puzzle->size == 1) {  // special case for size 1, no need to use a for loop
                fprintf(fp, "+---+\n| %d |\n+---+\n", puzzle->grid[0][0]);
            } else {
                int sqrt_size = sqrt(puzzle->size);
                int num_dashes = 2*sqrt_size;  // base number of dashes for horizontal border

                for (int i = 0; i < puzzle->size; i++) {
                    if (i == 0 || ((i % sqrt_size) == 0)) { // make above the border 
                        fancy_horz_border_helper(fp, num_dashes, sqrt_size);
                    }
                
                    for (int k = 0; k < puzzle->size; k++) {
                        if (k == 0) {
                            fprintf(fp, "| "); // pipe at beginning of row
                            print_box_value(fp, puzzle, puzzle->grid[i][k]);
                        }
                        else if (((k + 1) % sqrt_size) == 0 ) { // determines index to insert inner piping '|'
                            print_box_value(fp, puzzle, puzzle->grid[i][k]);
                            fprintf(fp, "| "); // pipe marking each section
                        } else {
                            print_box_value(fp, puzzle, puzzle->grid[i][k]);
                        }
                    } 
                    fprintf(fp, "\n"); // print next row of sudoku 
                }
                fancy_horz_border_helper(fp, num_dashes, sqrt_size); // print bottom horizontal border
                fprintf(fp, "\n");
            }
            
        } else {
            printf("\n(null)\n");
        }
    } else {
        fprintf(stderr, "FILE POINTER IS NULL\n\n");
    }
}

void 
fancy_horz_border_helper(FILE* fp, int border_box_size, int sqrt_size) 
{
    int puzzle_size = sqrt_size*sqrt_size;
    int extra_dashes;
    if (puzzle_size <= 9) { // number of extra dashes for single digit puzzle sizes
        extra_dashes = 1;  
    } else {    // number of extra dashes for double digit puzzle sizes
        extra_dashes = sqrt_size + 1; 
    }
    
    border_box_size = border_box_size + extra_dashes;   // total number of d
    for (int j = 0; j < sqrt_size; j++) {   // segment total line by + signs (+---...+)
        fprintf(fp, "+");
        for (int i = 0; i < border_box_size; i++) { // do dashes inside of + signs
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "+\n"); // new line 
}


/**************************  is_val_in_box() ***************************/
/* see puzzle.h for description */
bool 
is_val_in_box(puzzle_t* puzzle, int diag, int row, int column, int entry) {
    // if the entry is already in the (sqrt x sqrt) box
    if (puzzle != NULL) {
        int sqrt_size = sqrt(puzzle->size); 
        for (int i = 0; i < sqrt_size; i++) {
            for (int j = 0; j < sqrt_size; j++) {
                if (get_grid(puzzle)[diag+i][diag+j] == entry) {  // value in its surrounding sub-box of puzzle grid
                    return false;
                }
            } 
        }
        return true;
    } else {
        return true; // return true if puzzle is NULL
    }
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
  int puzzle_size = get_grid_size(puzzle);
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
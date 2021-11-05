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

#include "../solve/solve.h"
#include "../library/counters.h"
#include "../box/box.h"



/************************** file-local global variables   ***********************/
/* none */


/************************  static helper  functions  prototypes ******************/
/* that is, not visible outside this file */
static char* normalize_word(char* word);
static int count_num_solutions_helper(box_t* sudoku[9][9], char*level, int num_solutions, int init_row, int init_column);

static void hor_shift(box_t* sudoku[9][9]) ;
static void vert_shift(box_t* sudoku[9][9]) ;
/***************************** global functions *********************************/
/* that is, visible outside this file */
void sudoku_populate(box_t* sudoku[9][9]);
void remove_sudoku(box_t* sudoku[9][9], int num_left) ;

void sudoku_new(box_t* sudoku[9][9], const int SIZE);
void sudoku_print (box_t* sudoku[9][9], FILE* fp);
void sudoku_print_formated (box_t* sudoku[9][9], FILE* fp);
void sudoku_unsolved(box_t* sudoku[9][9], char* level);
void sudoku_create_puzzle(box_t* sudoku[9][9], char* level);
int count_num_solutions(box_t* sudoku[9][9], char* level) ;
bool val_not_in_cross_section(box_t* sudoku[9][9], int row, int column, int value, char* level);

/******************************* sudoku_create() ********************************/
/* see create.h for description */

void update_counters(box_t* sudoku[9][9]) {
    
    for(int i = 0; i < 9; i ++) {
      for(int j = 0; j < 9; j ++) {

        int v = get_value(sudoku[i][j]);
        if( v != 0){
            vertical_update(i,j,v,sudoku);
            horizontal_update(i,j,v,sudoku);
            box_update(i,j,v,sudoku);


        }
      }
    }
}

int sudoku_valid(box_t* sudoku[9][9])
 {

  for(int i = 0; i < 9; i ++) {
    for(int j = 0; j < 9; j ++) {
      if(get_value(sudoku[i][j]) == 0) {
        return 0;
      }
    }

  }
  return 1;
}


 void 
 sudoku_new(box_t* sudoku[9][9], const int SIZE)
 {
     
     // handle NULL sudoku
    if(sudoku == NULL){
        return;
    }
    for(int i=0;  i < SIZE ; i++) // rows
    {   
        for (int j = 0; j < SIZE; j++) // columns
        { 
          
          sudoku[i][j] = malloc(sizeof(box_t*));
          sudoku[i][j] = box_new(); // put a new box at each position in the 2D array/sudoku 

        }
    }

}


/******************************* sudoku_print() *************************************/
/* see create.h for description  */
void
sudoku_print (box_t* sudoku[9][9], FILE* fp){
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(sudoku == NULL){
        printf("(null)");
        return;
    }

    for( int i = 0; i < 9; i++){  // row
        for(int j= 0 ;j < 9; j++){  // column
           box_value_print(sudoku[i][j],fp); 
        }
        printf("\n"); // print next row of sudoku
    }

}

static void biterate(void *arg, const int key, const int count)
{
  int* a = arg;

  if(*a == -1) {
  }
  else if(*a != key && count == 1) {
    (*a) =-1;
  }
  

}

void vertical_c(int x, int y, int* value, box_t* sudoku[9][9])
{
  for (int j = 0; j < 9; j++) {
        if (j != x) {
            //int px = j + x;
            if(get_value(sudoku[j][y]) == 0) {
              counters_iterate(get_counter(sudoku[j][y]), value, biterate);
            }
        }
    }
}


void horizontal_c(int x, int y, int* value, box_t* sudoku[9][9])
{
    // i dont like this hardcoded
    for (int i = 0; i < 9; i++) {
        if (i != y) {
          if(get_value(sudoku[x][i]) == 0) {
           counters_iterate(get_counter(sudoku[x][i]), value, biterate);
            }
        }
    }
}

void box_c(int x, int y, int* value, box_t* sudoku[9][9]) 
{


  int ip;
  int jp;

  if(x%3 == 1) { 
    ip = -1;
  }
  else if(x%3 == 2) { 
    ip = -2;
  }
  else {
    ip = 0;
  }

  if(y%3 == 1) { 
    jp = -1;
  }
  else if(y%3 == 2) { 
    jp = -2;
  }
  else {
    jp = 0;
  }

  for(int i = ip ; i < (3 - (x%3)); i ++) {
    for(int j = jp ; j < (3 - (y%3)); j ++) {

      //Allows us to ignore points already reached by horizonal and vertical check
      // logic on adding x or y? 
      if(i != x || j != y) {
          if(get_value(sudoku[x+ i][y+j]) == 0) {
        counters_iterate(get_counter(sudoku[x + i][y+ j]), value, biterate);
          }
      }
      

    }
    
  }

}




/************************** sudoku_unsolved() **********************/
/* see create.h for description  */

void
sudoku_unsolved(box_t* sudoku[9][9], char* level){
/* see create.h for description */
    //srand(time(NULL));
   // ensure non- seed randomization here
    srand(time(NULL));

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

        do{
            // pick a random x
            random_box_x = rand() % 9; // from 0 to 8

            //pick a random y
            random_box_y = rand() % 9; // from 0 to 9
                
        }
        // check if the box at that location has values of zero
        // while we haven't found one, keep picking random x,y locations
        while(get_value(sudoku[random_box_x][random_box_y]) != 0);
                
            // keep cuurent random key and value 
            int random_key;
            int key_value;
            int h_valid;
            int v_valid;
            int b_valid;
            int valid;

            // next pick key from counter until found one whose key value is 1
            do{
                // pick a random key between 1 and 9 
                random_key = (rand() % 9 )+ 1; // from 1 to 9
                //gey key value form box's counterset
                key_value = counters_get(get_counter(sudoku[random_box_x][random_box_y]), random_key);

                h_valid = random_key;
                v_valid = random_key;
                b_valid = random_key;
                valid = random_key;

                if(key_value == 1) {
                  vertical_c(random_box_x, random_box_y, &v_valid, sudoku);
                  horizontal_c(random_box_x, random_box_y, &h_valid, sudoku);
                  box_c(random_box_x, random_box_y, &b_valid, sudoku);
                  if(h_valid == -1 && b_valid == -1 && v_valid == -1) {
                    valid = -1;
                  }

                }



            }

 
            // check if value of key in that box's counterset is 1
            // while its not, keep picking keys
            while(key_value !=1 && valid != -1);


            // set the key's value as value of the box
            set_value(sudoku[random_box_x][random_box_y], random_key);
             
            //sudoku[random_box_x][random_box_y]->value = random_key; 
            vertical_update(random_box_x,random_box_y,random_key,sudoku);
            horizontal_update(random_box_x,random_box_y,random_key,sudoku);
            box_update(random_box_x,random_box_y,random_key,sudoku);

            // update relevant coresponding row, cols, and box->ctr possible values affected by choice of key
            //sudoku_update_rows_cols_box(sudoku[9][9], random_box_x, random_box_y, key_value, level); // Veronica's to do  
    }  
}

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
















/*******************************  sudoku_update_rows_cols_box *****************************/
void sudoku_update_rows_cols_box(box_t* sudoku[9][9], int random_box_x,int random_box_y, int key_value, char* level){
    // to do
}

/******************************************************************************************/
/******************************************************************************************/
/***************** static    helper   methods   defined   here   **************************/
/******************************************************************************************/
/******************************************************************************************/
/* that is, not visible outside this file */

/********************* valueprint() ***********************/
/* helper method that prints the box value to  given file
 *
 */
static void valueprint(FILE* fp, int value)
{  
    //if(value != NULL){
        fprintf(fp, "%d ", value); 
  //}
}


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

void sudoku_populate(box_t* sudoku[9][9]) 
{

    int p = 0;
    for(int i = 0; i < 9; i ++) {
      for(int j = 0; j < 9; j ++) {
        if(i > 5) {
          int w = (p + j +3) %9;
          if (w==0) { set_value(sudoku[i][j],9 ); }
          else{ set_value(sudoku[i][j],w );} 
        }
        else if(i > 2) {
          int w = (p + j +2) %9;
          if (w==0) { set_value(sudoku[i][j],9); }
          else{ set_value(sudoku[i][j],w );}
        }
        else{
        set_value(sudoku[i][j],(p + j) %9 + 1);
        }
        
    }
    p = p+3 %9;
    }
}


void randomize_sudoku(box_t* sudoku[9][9]) 
{
  for(int i = 0; i < 10000; i ++) {
    
    int r = rand() % 2;
    if(r == 0) { hor_shift(sudoku); }
    else { vert_shift(sudoku); }
    
  }

} 

static void hor_shift(box_t* sudoku[9][9]) 
{     

  //pick a random column and random shift
  int y_1 = rand() % 9;
  int p = rand() % 2;


  int y_2;

  if(y_1%3 == 1) { 
    if(p == 0){ y_2 = y_1 +1; }
    else { y_2 = y_1 -1;}
  }
  else if(y_1%3 == 2) { 
    if(p == 0){ y_2 = y_1 -1; }
    else { y_2 = y_1 -2; }
  }
  else {
    if(p == 0){ y_2 = y_1 +1; }
    else { y_2 = y_1 +2; }
  }


  //Swap points
  for(int k = 0; k < 9; k ++) {
    int a = get_value(sudoku[k][y_1]);
    int b = get_value(sudoku[k][y_2]);
    set_value(sudoku[k][y_1], b);
    set_value(sudoku[k][y_2], a);
    }
}

static void vert_shift(box_t* sudoku[9][9]) 
{     
      //pick a random column and random shift
      int x_1 = rand() % 9;
      int p = rand() %2;

      int x_2;
      if(x_1%3 == 1) { 
        if(p == 0){ x_2 = x_1 +1; }
        else { x_2 = x_1 -1;}
      }
      else if(x_1%3 == 2) { 
        if(p == 0){ x_2 = x_1 -1; }
        else { x_2 = x_1 -2; }
      }
      else {
        if(p == 0){ x_2 = x_1 +1; }
        else { x_2 = x_1 +2; }
      }


      //Swap points
      for(int k = 0; k < 9; k ++) {
        int a = get_value(sudoku[x_1][k]);
        int b = get_value(sudoku[x_2][k]);
        set_value(sudoku[x_1][k], b);
        set_value(sudoku[x_2][k], a);
      }
}


void remove_sudoku(box_t* sudoku[9][9], int num_left) 
{
    //srand(time(NULL));

    for(int i = 0; i < 81-num_left; i ++) {
        
        int random_box_x;
        int random_box_y;
        box_t* s[9][9];
        do{
            // pick a random x
            random_box_x = rand() % 9; // from 0 to 8 

            //pick a random y
            random_box_y = rand() % 9; // from 0 to 8

            if(get_value(sudoku[random_box_x][random_box_y]) != 0) {

              //create new sudoku
              sudoku_new(s, 9);

              //populate it
              for(int i = 0; i < 9; i ++) {
                for(int j = 0; j < 9; j ++) {
                  set_value(s[i][j], get_value(sudoku[i][j]));
                }
              }

              //get rid of random point and see if it can still be solved
              set_value(s[random_box_x][random_box_y], 0);
              update_counters(s);
              solve_sudoku(s);
            

            }
                
        }
        // check if the box at that location has values of zero
        // while we haven't found one, keep picking random x,y locations
        while(sudoku_valid(s) != 1);

         set_value(sudoku[random_box_x][random_box_y], 0);
    }

    update_counters(sudoku);
}

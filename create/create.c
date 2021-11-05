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

static void hor_shift(box_t* sudoku[9][9]) ;
static void vert_shift(box_t* sudoku[9][9]) ;
/***************************** global functions *********************************/
/* that is, visible outside this file */
void sudoku_populate(box_t* sudoku[9][9]);
void remove_sudoku(box_t* sudoku[9][9], int num_left) ;
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

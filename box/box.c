/* 
 * BOX.c - CS50 'box' module
 *
 * see box.h for more information.
 * 
 * Authors:
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../library/counters.h"

/**************** file-local global variables ****************/
/* none */


/**************** global types ****************/
typedef struct box {
  int value;
  int size_of_grid;
  int x;    // x location on sudoku grid
  int y;   // y location on sudoku grid
  counters_t* ctr; // counter holding all possible values left 
} box_t;

/********************************* global functions ********************/
/* that is, visible outside this file */


/*********************** box_new() *******************/
/* see box.h for description*/

box_t* box_new(int size_of_grid)
{
  box_t* box = malloc(sizeof(box_t));
  
  if (box == NULL) 
  {
    return NULL; // error allocating box
  } 
  else {

    // initialize contents of box structure
    box->value = 0;      // initialize value to zero
    box->size_of_grid = size_of_grid; // keep track of overall grid size in individual boz
    box->ctr = counters_new();   // hold all possible values 1 through grid size in here

    for(int i=1; i <= size_of_grid;i++){
        counters_add(box->ctr, i); // add all number 1-9 ass possible values of counters
    }
    return box;
  }
    
}



/********************** box_value_print() *****************/
/* see box.h for description*/
void box_value_print(box_t* box, FILE* fp){

    if (fp != NULL){
        if (box != NULL){
          printf("%d ", box->value); //print  box's value
        }
    }
}



/************************** get_box_counter() ***************/
/* see box.h for description*/
counters_t* get_counter(box_t* box) {

  if(box == NULL){ // return if box is NULL
    return NULL;
  }
  // otherwise return counter of given box
  return box->ctr;
}



/***************************** get_value() *******************/
/* see box.h for description*/
int get_value(box_t* box){

  if(box == NULL){ // return if box is NULL
    return -1;
  }
  return box->value;
}



/****************************** set_value() *******************/
/* see box.h for description*/
void set_value(box_t* box, int val){

  if(box == NULL || val < 0 || val > box->size_of_grid) // handle NULL and negative cases 
  {
    return;
  }
  // otherwise set the value of the bax
  box->value = val;
}

int get_grid_size_from_box(box_t* box) 
{
  if (box != NULL) {
    return box->size_of_grid;
  }
  return -1;
}

// /************************* box_delete() ********************/
/* see box.h for description*/
static void box_delete(box_t *box)
{
    if (box != NULL){
        counters_delete(box->ctr);
        free(box);
    }
    
}


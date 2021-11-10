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
#include <math.h>
#include "../library/counters.h"

/**************** file-local global variables ****************/
/* none */


/**************** global types ****************/
typedef struct box {
  int value;
  int size_of_grid;
  int x;    // x location on sudoku grid
  int y;   // y location on sudoku grid
  counters_t* range; // counter holding all possible values left 
  counters_t* visited; // counter holding all possible values left
} box_t;

/********************************* global functions ********************/
/* that is, visible outside this file */


/*********************** box_new() *******************/
/* see box.h for description*/

box_t* box_new(int size_of_grid)
{
  box_t* box = malloc(sizeof(box_t));
  
  if (box == NULL) {
    return NULL; // error allocating box
  } 
  else {

    double sqrt_of_size = sqrt(size_of_grid);
    // initialize contents of box structure
    if (size_of_grid > 0 && ceil(sqrt_of_size) == floor(sqrt_of_size)) {  // check if perfect square
        box->value = 0;      // initialize value to zero
        box->range = counters_new();   // hold all possible values 1 through 9 in here
        box->visited = counters_new();
        box->size_of_grid = size_of_grid; // keep track of overall grid size in individual boz
    // ****** need to check if size_of_grid is a perfect square!!!
        for(int i=1; i <= size_of_grid;i++){
            counters_add(box->range, i); // add all number 1-9 ass possible values of counters
            counters_add(box->visited, i); 
        }
        return box;
    } else {
      return NULL;
    }
    
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
counters_t* get_counter(box_t* box) {  // ********should be range!!!!!!!!!

  if(box == NULL){ // return if box is NULL
    return NULL;
  }
  // otherwise return counter of given box
  return box->range;
}

counters_t* get_visited(box_t* box)
 {

  if(box == NULL){ // return if box is NULL
    return NULL;
  }
  // otherwise return counter of given box
  return box->visited;
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

    if(box != NULL) {
        if (val < 0 || val > box->size_of_grid)  {// handle NULL and negative cases 
            box->value = -1;
        } else {  // otherwise set the value of the bax
            box->value = val;
        }
    } 
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
void box_delete(box_t *box)
{
    if (box != NULL){
        counters_delete(box->range);
        free(box);
    }
    
}

void reset_box(box_t* box) 
{
    if (box != NULL) {
        for(int i=1; i <= 9;i++){
            counters_set(box->range, i, 1); // add all number 1-9 ass possible values of counters
        }
    }
}

void reset_visited(box_t* box) 
{
    if (box != NULL) {
        for(int i=1; i <= 9;i++){
            counters_set(box->visited, i, 1); // add all number 1-9 ass possible values of counters
        }
    }
}
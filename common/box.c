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
  counters_t* ctr;
} box_t;

/********************************* global functions ********************/
/* that is, visible outside this file */


/*********************** counters_new() *******************/
/* see box.h for description*/

box_t* box_new(void)
{

    box_t* box = malloc(sizeof(box_t));

    if (box == NULL) {
    return NULL; // error allocating box
    } 
    else {
    // initialize contents of box structure
    box->value = 0;   // initialize value to zero
    box->ctr = counters_new();   // hold all possible values 1 through 9 in here

    for(int i=1; i <= 9;i++){
        counters_add(box->ctr, i);
    }
    return box;
  }
    
}



/********************** box_value_print() *****************/
/* see box.h for description*/
void box_value_print(box_t* box, FILE* fp, void (*valueprint)(FILE* fp, void* item)){

    if (fp != NULL){
        if (box != NULL){
          printf("%d ", box->value);
            if(valueprint != NULL){
                (*valueprint)(fp, box->value); 
            }
        }
    }
}



/************************* box_delete ********************/
/* see box.h for description*/
static void box_delete(box_t *box)
{
    if (box != NULL){
        counters_delete(box->ctr);
    }
}



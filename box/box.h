/* 
 * box.h - header file for CS50 'box' module
 *
 * A "box" holds the current value at a position in a sudoku
 * puzzle and a counter set of all allowable values at that position. 
 * If a value in the box counterset is 0, that value is not a possible value for
 * that position, otherwise it is.
 * A new box is instantiated by simply calling box_new. To delete the box,
 * caller may simply caall box_delete.
 * 
 * 
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 * 
 */

#ifndef __BOX_H
#define __BOX_H

#include <stdio.h>
#include <stdbool.h>
#include "../library/counters.h"


/**************** global types ****************/
typedef struct box box_t;

/********************** functions *******************/


/********************* box_new() *********************/
/* Create a new (empty) box structure.
 *
 * We return:
 *   pointer to a new box; NULL if error. 
 * We guarantee:
 *   box t is intialized empty.
 * Caller is responsible for:
 *   later calling box_delete();
 */
box_t* box_new(int size_of_grid);

counters_t* get_visited(box_t* box);

/********************** box_value_print() *****************/
/* Print the value of a box to file
 * Caller provides box  the file to print to 
 * We do nothing if file pointer is null,
 * do nothing if box is null
 * 
 */ 
void box_value_print(box_t* box, FILE* fp);


/******************** get_counter() *************************/
/* gets the counter of a given box
 * We return a counter if the box is not null
 * Caller provides the box whose counter were to extract 
 * 
 */
counters_t* get_counter(box_t* box);



/******************** set_value()  ***************************/
/* Sets a given value to that of the given box 
 * User provides box and value
 * return  from fucntion if value is < 0
 * or box is NULL
 *
 */
void set_value(box_t* box, int val);
 


/********************get_value() *****************************/
/* Return the value of a given box
 * User prvides the box whose value is desired
 * We return from function if the box is  NULL
 * 
 */
int get_value(box_t* box); 

int get_grid_size_from_box(box_t* box);

/********************* box_delete() *********************/
/* Delete the whole box.
 * Caller provides:
 *   a valid pointer to a box.
 * We do:
 *   we ignore NULL boxes.
 *   we free all memory we allocate for this box.
 */
void box_delete(box_t *box);

int get_iteration(box_t* box);
void reset_box(box_t* box) ;
int reset_iteration(box_t* box);
int inc_iteration(box_t* box) ;
void reset_visited(box_t* box) ;

#endif // __BOX_H





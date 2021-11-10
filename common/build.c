#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "../puzzle/puzzle.h"
#include "../library/counters.h"

/**************** local functions ****************/
/* not visible outside this file */
static void visited_iterate(void *arg, const int key, const int count);
static void range_iterate(void *arg, const int key, const int count);
static void counter_size(void *arg, const int key, const int count); 


/**************** build_sudoku() ****************/
/* see build.h for description */
bool build_sudoku(puzzle_t* puzzle, char* mode)
{   
  //If the mode is solve, create the a puzzle with original inputs
  puzzle_t* copy= puzzle_new(9);

  if(strcmp(mode, "solve") == 0) {

    
    for(int i = 0; i < 9; i ++) {
      for(int j = 0; j < 9; j ++ ) {
        set_box_in_grid(copy, get_box_from_grid(puzzle, i,j), i, j);
      }
    }

  }

  //Initialize variables
  int i;
  int j;
  int prev_i;
  int prev_j;
  int random_key;
  int key_value;
  int visit_value;
  

  //loop through each point point
  int k = 0;

  while(k<81){

    //reset the box and update all the counters
    reset_all(puzzle);
    update_all_box_counters(puzzle);

    //get the current point
    i = k/9;
    j = k%9;

    //If we are in solve mode and at a point set at input, ignore
    while(strcmp(mode, "create") != 0 && k < 81 && get_box_value(copy, i, j) != 0) {

        k += 1;
        i = k/9;
        j = k%9;

    }

    //If we leave the grid, the sudoku is solved
    if(k >= 81) {
      return true;
    }


    //Get the number of options for a point
    int options = 0;

    counters_t* temp = counters_new();

    
    counters_iterate(get_visited(get_box_from_grid(puzzle,i,j)), temp, visited_iterate);
    counters_iterate(get_counter(get_box_from_grid(puzzle,i,j)), temp, range_iterate);

    counters_iterate(temp, &options, counter_size);  

    //If the point has no psosible values, backtrack
    if(options == 0) {

      //get the current value form the previous point
      prev_i = (k-1)/9;
      prev_j = (k-1)%9;


      //reset the previous point to 0
      set_value(get_box_from_grid(puzzle,prev_i,prev_j), 0);

      //reset visited on current point     
      reset_visited(get_box_from_grid(puzzle,i,j));

      

      //This works but is chunky as fuck
      //Still dont handle an unsolvalbe sudoku
      if(strcmp(mode, "solve") == 0) {
        k = 0;
      }
      else{
        k -= 1;
      }


      //prev_i = (k-1)/9;
      //prev_j = (k-1)%9;
      //If we are in solve mode and at a point set at input, ignore
      //while(strcmp(mode, "create") != 0 && k >= 0 && get_box_value(copy, prev_i, prev_j) != 0) {
      
      //  k -= 1;
      //  prev_i = (k-1)/9;
      //  prev_j = (k-1)%9;

      //}
      //The sudoku is unsolvalbe
      if(k < 0) {
        return false;
      }

    }
    else{

        int valid = 0;

      do {
        
        //Get a random key
        random_key = (rand() % 9 )+ 1; // from 1 to 9      

        //check if the key is valid for the range counter and visited counter
        key_value = get_box_count(puzzle, i,j, random_key);
        visit_value = get_visit_count(puzzle, i,j, random_key);

        //If the key is valid, set valie
        if(key_value == 1 && visit_value == 1) {
          valid = 1;
        }

      } 
      //continue to get a new key until the random key is valid
      while(valid != 1);

      //set the value
      set_value(get_box_from_grid(puzzle,i,j), random_key);
      
      //tell the point it can't visit the key anymore
      counters_set(get_visited(get_box_from_grid(puzzle,i,j)), random_key, 0);

      //Increment k
      k += 1;
    }
  }

  //Return true to indicate the puzzle was created or solved successfully
  return true;

}



/**************** visited_iterate ****************/
/* 
 * Iterator which adds each element in the visited counter to the options counter
*/
static void visited_iterate(void *arg, const int key, const int count)
{
  counters_t* a = arg;
  if(count == 1){
    counters_add(a, key);

  }

}

/**************** range_iterate ****************/
/* 
 * Iterator which adds each element in the range counter to the options counter
*/
static void range_iterate(void *arg, const int key, const int count)
{
  counters_t* a = arg;
  if(count == 1){
    counters_add(a, key);

  }

}

/**************** counter_size ****************/
/* 
 * Iterator which increments an options counter if a number exists in the range and visited counter
*/
static void counter_size(void *arg, const int key, const int count)
{
  int* options = arg;
  if(count == 2) {
    (*options) ++;
  }
}

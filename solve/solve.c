
//global types and constant definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../library/counters.h"
#include "../box/box.h"
#include "../create/create.h"

static void solve_iterate(void *arg, const int key, const int count);


void solve_sudoku(puzzle_t* puzzle)
{   
  bool repeat = false;

    for(int i = 0; i < 9; i ++) {
      for(int j = 0; j < 9; j ++) {
        
        //Check the box's value is not already set
        if(get_box_value(puzzle, i, j) == 0) {
          
          //iterate through and identify what the value could be 
          int possible_value = 0;
          counters_iterate(get_counter(get_box_from_grid(puzzle,i,j)), &possible_value, solve_iterate);
          
          //If the point only has one possibility, set it and update adjacent points
          if(possible_value != -1 && possible_value != 0) {
            
            repeat = true;

            //Set point
            set_value(get_box_from_grid(puzzle,i,j), possible_value);

            //go through and update other points
            update_adjacent_box_counters(puzzle, i, j, possible_value);

          }
        }
    }
  }

  if(repeat) {
    solve_sudoku(puzzle);
  }



}


//Iterate through each key in the counter. If its the first possible one seen, set it as a possible value
//If it the second, set the possible_value to -1
static void solve_iterate(void *arg, const int key, const int count)
{
  int* a = arg;

  if(*a == -1) {
  }
  else if(*a == 0 && count == 1) {
    (*a) +=key;
  }
  else if(*a != 0 && count == 1) {
    (*a) =-1;
  }
  
}


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
#include "../puzzle/puzzle.h"



static void visited_iterate(void *arg, const int key, const int count)
{
  counters_t* a = arg;
  if(count == 1){
    counters_add(a, key);

  }

}

static void range_iterate(void *arg, const int key, const int count)
{
  counters_t* a = arg;
  if(count == 1){
    counters_add(a, key);

  }

}

static void counter_size(void *arg, const int key, const int count)
{
  int* a = arg;
  if(count == 2) {
    (*a) ++;
  }
}


void
build_sudoku(puzzle_t* puzzle, char* level)
{   

  int random_key;
  int key_value;
  int visit_value;
  

  //loop through ever point
  int k = 0;

  while(k<81){

    //reset the box and update all the counters
    reset_all(puzzle);
    update_all_box_counters(puzzle);

    //get the current point
    int i = k/9;
    int j = k%9;

    //Get the number of options for a point
    int options = 0;


    counters_t* temp = counters_new();

    
    counters_iterate(get_visited(get_box_from_grid(puzzle,i,j)), temp, visited_iterate);
    counters_iterate(get_counter(get_box_from_grid(puzzle,i,j)), temp, range_iterate);

    counters_iterate(temp, &options, counter_size);  

    //If the point has no psosible values, backtrack
    if(options == 0) {

      //get the current value form the previous point
      int prev_i = (k-1)/9;
      int prev_j = (k-1)%9;


      //reset the previous point to 0
      set_value(get_box_from_grid(puzzle,prev_i,prev_j), 0);

      //reset visited on current point     
      reset_visited(get_box_from_grid(puzzle,i,j));

      k -= 1;

    }
    else{
        int valid = 0;
      do {

        random_key = (rand() % 9 )+ 1; // from 1 to 9      

        key_value = get_box_count(puzzle, i,j, random_key);
        visit_value = get_visit_count(puzzle, i,j, random_key);

        if(key_value == 1 && visit_value == 1) {
          valid = 1;
        }

       } 
      
      //go while the key is valid and the point has not been visited
      while(valid != 1);

      //set the value
      set_value(get_box_from_grid(puzzle,i,j), random_key);
      
      //tell the point it cant visit the key anymore
      counters_set(get_visited(get_box_from_grid(puzzle,i,j)), random_key, 0);

      k += 1;
  }


  }

}
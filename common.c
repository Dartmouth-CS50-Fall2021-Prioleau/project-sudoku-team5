
//find 4 corners
//add their values to the bag if count is 1

//global types and constant definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../libcs50/counters.h"
#include "../libcs50/bag.h"

void box_available(int x, int y, counters_t* main) ;
void A_and_B_merge_helper(void *arg, const int key, const int count);

counters_t* check_availabilty(int x, int y)  {

  //Initialize the main counter (we can also have a main counter passed in to save time/sapce)
  counters_t* main = counters_new();
  for(int t = 1; t < 10; t ++) {
    counters_add(main, t);
  }

  horizonal_available(x,y,main);
  vertical_available(x,y,main);
  box_available(x,y,main);

  return main;

}


//Given 3 bags and them
void box_available(int x, int y, counters_t* main) 
{


  int i;
  int j;

  if(x%3 == 1) { 
    i = 0;
  }
  else if(x%3 == 2) { 
    i = -1;
  }
  else {
    i = 0;
  }

  if(y%3 == 1) { 
    j = 0;
  }
  else if(y%3 == 2) { 
    j = -1;
  }
  else {
    j = 0;
  }

  for( ; i < 3 - (x%3); i ++ ) {
    for( ; j < 3 - (j%3); j ++ ) {

      //Allows us to ignore points already reached by horizonal and vertical check
      if(i != x || j != y) {
        int px = x + i;
        int py = y + j;

        counters_t* curr = sudoku[px][py];

        update_range(curr, main); 
      }
      

    }
    
  }

}

void update_range(counters_t* countersA, counters_t* countersB) {

  //Update counts in B to 0 if they are 0 in A
  counters_iterate(countersA, countersB, A_and_B_merge_helper);
  
}

void A_and_B_merge_helper(void *arg, const int key, const int count)
{
  counters_t *countersB = arg;
  
  //If the count is 0 in A, set it to 0 in Bs
  if (count == 0) {
    counters_set(countersB, key, 0);
  }

}

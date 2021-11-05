
//global types and constant definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../library/counters.h"
#include "../box/box.h"
#include "../create/create.h"

static void boxiterate(void *arg, const int key, const int count);
void vertical_update(int x, int y, int value, box_t* sudoku[9][9]);
void horizontal_update(int x, int y, int value, box_t* sudoku[9][9]);
void box_update(int x, int y, int value, box_t* sudoku[9][9]) ;

void solve_sudoku(box_t* sudoku[9][9])
{   bool repeat = false;

    for(int i = 0; i < 9; i ++) {
      for(int j = 0; j < 9; j ++) {

        if(get_value(sudoku[i][j]) == 0) {
          
          int count_size = 0;
          counters_iterate(get_counter(sudoku[i][j]), &count_size, boxiterate);
          //If we see a single point set it!
          //printf("%d", count_size);
          if(count_size != -1 && count_size != 0) {
            
            repeat = true;
            //Set point
            set_value(sudoku[i][j], count_size);

            //go through and update other points
            vertical_update(i,j,count_size,sudoku);
            horizontal_update(i,j,count_size,sudoku);
            box_update(i,j,count_size,sudoku);

          }
          
        }

    }

  }

  if(repeat) {
    solve_sudoku(sudoku);
  }



}



static void boxiterate(void *arg, const int key, const int count)
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

void vertical_update(int x, int y, int value, box_t* sudoku[9][9])
{
  for (int j = 0; j < 9; j++) {
        if (j != x) {
            //int px = j + x;
             if(get_value(sudoku[j][y]) == 0) {
            counters_set(get_counter(sudoku[j][y]), value, 0);
             }
        }
    }
}


void horizontal_update(int x, int y, int value, box_t* sudoku[9][9])
{
    // i dont like this hardcoded
    for (int i = 0; i < 9; i++) {
        if (i != y) {
          if(get_value(sudoku[x][i]) == 0) {
            counters_set(get_counter(sudoku[x][i]), value, 0);
          }
        }
    }
}


void box_update(int x, int y, int value, box_t* sudoku[9][9]) 
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
        counters_set(get_counter(sudoku[x + i][y+ j]), value, 0);
        }
      }
      

    }
    
  }

}

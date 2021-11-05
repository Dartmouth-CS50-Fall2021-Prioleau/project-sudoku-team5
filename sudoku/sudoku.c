#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "../create/create.h"
#include "../common/box.h"
#include "../library/memory.h"
#include "../library/counters.h"
#include "../solve/solve.c"
#include "../create/create.h"

int sudoku_valid(box_t* sudoku[9][9]);
void sudoku_populate(box_t* sudoku[9][9]) ;
void hor_shift(box_t* sudoku[9][9]) ;
void vert_shift(box_t* sudoku[9][9]);


int main(const int argc, const char** argv)
{

  //check for valid number of parameters
  if (argc != 3) {

    fprintf(stderr, "Incorrect number of arguemnts. ");
    fprintf(stderr,"Should have ./sudoku mode difficulty\n");
    return 1;

  }
  
  char* mode = malloc(strlen(argv[1]) * sizeof(char) + 1);
  char* difficulty = malloc(strlen(argv[2]) * sizeof(char) + 1);

  strcpy(mode, argv[1]);
  strcpy(difficulty, argv[2]);
    box_t* sudoku[9][9];

    sudoku_new(sudoku, 9);
    sudoku_populate(sudoku);


    srand(time(NULL));
    printf("populated puzzle sudoku ...\n");
    sudoku_print(sudoku, stdout);
    printf("\n"); 
    printf(" loading ...\n");

    for(int i = 0; i < 10; i ++) {
    hor_shift(sudoku);
    vert_shift(sudoku);
    }
    


    sudoku_print(sudoku, stdout);
    printf("creating puzzle ...\n");
    sudoku_create_puzzle(sudoku, difficulty);
    
    sudoku_print(sudoku, stdout);
    printf("counting numsolutions.. \n");
    int num = count_num_solutions(sudoku, difficulty);
    printf("num solutions %d \n", num);

    printf("\nsolving puzzle.. \n");
    solve_sudoku(sudoku);
    sudoku_print(sudoku, stdout);
    
}






void sudoku_populate(box_t* sudoku[9][9]) 
{

    int p = 0;
    for(int i = 0; i < 9; i ++) {
     
      for(int j = 0; j < 9; j ++) {
        if(i > 5) {
          int w = (p + j +3) %9;
          if (w==0) {
            set_value(sudoku[i][j],9 );
          }
          else{
            set_value(sudoku[i][j],w );
          } 
        }
        else if(i > 2) {
          int w = (p + j +2) %9;
          if (w==0) {
            set_value(sudoku[i][j],9 );
          }
          else{
            set_value(sudoku[i][j],w );
          }
          
        }
        else{
        set_value(sudoku[i][j],(p + j) %9 + 1);
        }
        
    }
    p = p+3 %9;
    }
}

void hor_shift(box_t* sudoku[9][9]) 
{

      int x = rand() % 9;
      int x_2;
      int ip;
      if(x%3 == 1) { 
        ip = rand() %2;
        if(ip == 0){
          x_2 = x +1;
        }
        else {
          x_2 = x -1; 
        }
      }
      else if(x%3 == 2) { 
        ip = rand() %2;
        if(ip == 0){
          x_2 = x -1;
        }
        else {
          x_2 = x -2; 
        }
      }
      else {
         ip = rand() %2;
        if(ip == 0){
          x_2 = x +1;
        }
        else {
          x_2 = x +2; 
        }
      }
      for(int k = 0; k < 9; k ++) {
        int a = get_value(sudoku[x][k]);
        int b = get_value(sudoku[x_2][k]);
        set_value(sudoku[x][k], b);
        set_value(sudoku[x_2][k], a);
      }
    

}

void vert_shift(box_t* sudoku[9][9]) 
{
      int x = rand() % 9;
      int x_2;
      int ip;
      if(x%3 == 1) { 
        ip = rand() %2;
        if(ip == 0){
          x_2 = x +1;
        }
        else {
          x_2 = x -1; 
        }
      }
      else if(x%3 == 2) { 
        ip = rand() %2;
        if(ip == 0){
          x_2 = x -1;
        }
        else {
          x_2 = x -2; 
        }
      }
      else {
         ip = rand() %2;
        if(ip == 0){
          x_2 = x +1;
        }
        else {
          x_2 = x +2; 
        }
      }
      for(int k = 0; k < 9; k ++) {
        int a = get_value(sudoku[k][x]);
        int b = get_value(sudoku[k][x_2]);
        set_value(sudoku[k][x], b);
        set_value(sudoku[k][x_2], a);
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







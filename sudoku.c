#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "./create/create.h"
#include "./box/box.h"
#include "./library/memory.h"
#include "./library/counters.h"
#include "./solve/solve.h"

int sudoku_valid(box_t* sudoku[9][9]);
void sudoku_populate(box_t* sudoku[9][9]) ;
void hor_shift(box_t* sudoku[9][9]) ;
void vert_shift(box_t* sudoku[9][9]);

int main(const int argc, const char** argv)
{

  //check for valid number of parameters
  if (argc != 3) {

    fprintf(stderr, "Incorrect number of arguments. ");
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

   time_t t;
   
   srand((unsigned) time(&t));

   /* Intializes random number generator */
   srand((unsigned) time(&t));
    

  sudoku_print(sudoku, stdout);
  printf("\n");

  randomize_sudoku(sudoku);

  sudoku_print(sudoku, stdout);
  printf("\n");

  remove_sudoku(sudoku, 25);

  sudoku_print(sudoku, stdout);

  solve_sudoku(sudoku);
      
  printf("\n");

  sudoku_print(sudoku, stdout);

}

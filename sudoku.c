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
#include "./puzzle/puzzle.h"


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

  //box_t* sudoku[9][9];
  puzzle_t* puzzle = puzzle_new(9);

  //sudoku_populate(sudoku);

   time_t t;
   
   srand((unsigned) time(&t));

    
  puzzle_print(puzzle, stdout);

  printf("\n");

  sudoku_unsolved(puzzle, difficulty);

  printf("\n");

  puzzle_print(puzzle, stdout);

  printf("\n");


  update_all_box_counters(puzzle, 1, 2, 3);

  solve_sudoku(puzzle);

  puzzle_print(puzzle, stdout);

      
  printf("\n");

  //sudoku_print(sudoku, stdout);

}
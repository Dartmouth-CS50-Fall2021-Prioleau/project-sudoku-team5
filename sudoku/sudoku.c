#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../create/create.h"
#include "../common/box.h"
#include "../library/memory.h"
#include "../library/counters.h"

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
  //sudoku_print(sudoku, stdout);
  printf("\n");
  sudoku_unsolved(sudoku, difficulty);
  sudoku_print(sudoku, stdout);
  //sudoku_print_formated(sudoku, stdout);

}




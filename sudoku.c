#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


int main(const int argc, const char** argv)
{

  //check for valid number of parameters
  if (argc != 3) {

    fprintf(stderr, "Incorrect number of arguemnts. ");
    fprintf(stderr,"Should have ./sudoku mode difficulty\n");
    return 1;

  }
  
  char* mode = assertp(malloc(strlen(argv[1]) * sizeof(char) + 1), "Error allocating for mode");
  char* difficulty = assertp(malloc(strlen(argv[2]) * sizeof(char) + 1), "Error allocating for difficulty");

  strcpy(mode, argv[1]);
  strcpy(difficulty, argv[2]);


}

/*
suduko_t* create(char* mode) {


}


suduko_t* solve(suduko_t* unsolved) {


}

*/
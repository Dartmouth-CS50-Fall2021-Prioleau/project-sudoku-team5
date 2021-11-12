/*
 * sudoku.c - CS50 Project 'sudoku' module
 *
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "./create/create.h"
#include "./solve/solve.h"
#include "./puzzle/puzzle.h"
//#include "./library/file.h"



//bool parse_user_sudoku(FILE* fp, puzzle_t* puzzle);

/*********** protoptypes ***************/
//bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle, char* level);



int main(const int argc, const char** argv)
{

  //check for valid number of parameters
  if (argc != 3 && argc != 2) {

    fprintf(stderr, "Incorrect number of arguments. ");
    fprintf(stderr,"Usage: ./sudoku mode difficulty\n");
    return 1;

  }


  char* mode;
  char* difficulty; 

  //Allocate space and copy to variable for inputs
  if(argc == 2) {
    mode = malloc(strlen(argv[1]) * sizeof(char) + 1);
    strcpy(mode, argv[1]);
  }

  else {
    mode = malloc(strlen(argv[1]) * sizeof(char) + 1);
    difficulty = malloc(strlen(argv[2]) * sizeof(char) + 1);
    strcpy(mode, argv[1]);
    strcpy(difficulty, argv[2]);
  }


  //Check mode and difficulty are valid
  if(strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0) {
    fprintf(stderr, "Mode must be 'create' or 'solve'\n");
    free(mode);
    return 2;
  }

  if(argc == 3 ) {
    if(strcmp(difficulty, "easy") != 0 && strcmp(difficulty, "hard") != 0) {
    fprintf(stderr, "Difficulty must be 'easy' or 'hard'\n");
    free(mode);
    return 2;
    }
  }

  //If 2 arguments are given make sure mode is solve
  if(argc == 2 && strcmp(mode, "create") == 0 ) {
    fprintf(stderr, "Create mode requires a third arguemnt for the difficulty\n");
    free(mode);
    return 3;
  } 

  time_t t;
  srand((unsigned) time(&t));

  //printf("hi\n");

  //check the mode
  if(strcmp(mode, "create") == 0) {
    
    puzzle_t* puzzle = puzzle_new(9);


    //build a full, complete sudoku
    build_full_sudoku(puzzle, difficulty);


    // delete num from fully built sudoku
    create_sudoku(puzzle, difficulty);

    //solve_sudoku(puzzle,0,0,difficulty);
    
    puzzle_print_formated(stdout, puzzle);


}  
   else { 
         // initialize sudoku to new one
         puzzle_t* parsed = puzzle_new(4);
         // read from stdin
         FILE* file  = stdin;
         // try parsing puzzle from stdin
         bool status = parse_user_puzzle(file, parsed);

         if (!status)
         {
            fprintf(stderr, "Format Error: Could not parsed puzzle.\n");
            return 3;

         } 
         else{

           if(!is_valid_unsolved(parsed)) {
              fprintf(stderr, "Invalid sudoku provided.\n");
              return 4;
           }

          solve_sudoku(parsed,0 ,0 ,"easy");

          puzzle_print_formated(stdout, parsed);
        }
   }
}

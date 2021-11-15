/* 
 * create.c - CS50 Sudoku Project 'sudoku ' module
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *  
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
 *
 * Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
 * November 02, 2021.
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






/***************************** protoptypes ***********************/
//bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle, char* level);


/**************************** main ****************************/
int main(const int argc, const char** argv)
{

  //check for valid number of parameters
  if (argc != 3 && argc != 2 && argc != 4) {

    fprintf(stderr, "Incorrect number of arguments. ");
    fprintf(stderr,"Usage: ./sudoku mode difficulty size\n");
    return 1;

  }


  char* mode;
  char* difficulty; 
  int size = 9;

  //Allocate space and copy to variable for inputs
  if(argc >= 2) {
    mode = count_calloc_assert(strlen(argv[1]), sizeof(char) + 1, "mode");
    strcpy(mode, argv[1]);
  }

  if (argc >= 3){
    difficulty = count_calloc_assert(strlen(argv[2]), sizeof(char) + 1, "difficulty");
    strcpy(difficulty, argv[2]);
  }

  if (argc >= 4){
    if(sscanf(argv[3], "%d", &size) < 1) {
      fprintf(stderr, "Error: Please input a valid integer for size\n");
      
      free(mode);
      free(difficulty);

      return 2;
    }
  }


  //Check mode and difficulty are valid
  if(strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0) {
    fprintf(stderr, "Mode must be 'create' or 'solve'\n");
    
    // check that number of received arguments is 3
    free(mode);
    if(argc >= 3) { free(difficulty); }


    return 2;
  }

  if(argc >= 3 && strcmp(difficulty, "easy") != 0 && strcmp(difficulty, "hard") != 0) {

    fprintf(stderr, "Difficulty must be 'easy' or 'hard'\n");

    free(mode); // remember to free malloc'd spaced ( on heap)
    free(difficulty); // """

    return 2;
    
  }

  //If 2 arguments are given make sure mode is solve
  if(argc == 2 && strcmp(mode, "create") == 0 ) {
    fprintf(stderr, "Create mode requires a third arguemnt for the difficulty\n");
    free(mode);
    return 2;
  } 

  // seed the randomization for debugging purposes
  time_t t;
  srand((unsigned) time(&t));


  //check the mode
  if(strcmp(mode, "create") == 0) 
  {
    
    puzzle_t* puzzle = puzzle_new(size); // create new puzzle  w/ entries initialized to zero

    if(puzzle == NULL) {
      printf("Unsuccessful creating puzzle\n");
      free(mode);
      if(argc >= 3) {free(difficulty);}
      return 5;
    }

    //build a full, complete sudoku
    build_full_sudoku(puzzle, difficulty);

    // delete points from fully built sudoku
    create_sudoku(puzzle, difficulty);

    //Print up the created sudoku
    puzzle_print_formated(stdout, puzzle);

    //Clean up for create:
    free(mode);
    if(argc >= 3) {free(difficulty);}
    puzzle_delete(puzzle);


  }  
  else 
  { 
    // initialize sudoku to new one
    puzzle_t* parsed = puzzle_new(size);

    if(parsed == NULL) {
      printf("Unsuccessful creating puzzle");
      free(mode);
      if(argc >= 3) {free(difficulty);}
      return 5;
    }
    
    // read from stdin
    FILE* file  = stdin;
    
    // try parsing puzzle from stdin
    bool status = parse_user_puzzle(file, parsed);

    //If the parsing fails
    if (!status)
    {
      fprintf(stderr, "Format Error: Could not parsed puzzle.\n");

      //Clean up for solve:
      free(mode);
      if(argc >= 3) {free(difficulty);}
      puzzle_delete(parsed);
      fclose(file);

      return 3;

    } 
    else{

      //If the given puzzle is not valid (less than 25 numbers or doesn't follow rules)
      if(!is_valid_unsolved(parsed)) {
      fprintf(stderr, "Invalid sudoku provided.\n");

      //Clean up for solve:
      free(mode);
      if(argc == 3) { free(difficulty); }
      puzzle_delete(parsed);
      fclose(file);
        
      return 4;
    }

    solve_sudoku(parsed,0 ,0 ,"easy");

    puzzle_print_formated(stdout, parsed);
    }

    //Clean up for solve:
    free(mode);
    if(argc >= 3) { free(difficulty); }
    puzzle_delete(parsed);
    fclose(file);
   }

  return 0;
}


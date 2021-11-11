#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "./library/memory.h"
#include "./library/counters.h"
#include "./library/file.h"
#include "./puzzle/puzzle.h"
#include "./create/create.h"

#include "./common/unique.h"

bool parse_user_sudoku(FILE* fp, puzzle_t* puzzle, int c);

/*********** protoptypes ***************/
bool parse_user_puzzle(FILE* fp, puzzle_t* puzzle, char* level);



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

  //check the mode
  if(strcmp(mode, "create") == 0) {
    

    printf("empty puzzle: \n\n");
    puzzle_t* puzzle = puzzle_new(9);

    puzzle_print_simple(puzzle, stdout);

    printf("full puzzle: \n\n");

    solve_sudoku(puzzle,0 ,0,difficulty);

    puzzle_print_simple(puzzle, stdout);
    printf("\n");

    create_sudoku(puzzle, difficulty);
      
    puzzle_print_simple(puzzle, stdout);

    solve_sudoku(puzzle,0 ,0,difficulty);

    printf("fully  built sudoku: \n\n");
    puzzle_print_simple(puzzle, stdout);
    //printf("\n\n");

  
}  

  else {
    
    char* unsolved;

    //Allow the user to input a sudoku or read in a piped in created sudoku


    puzzle_t* parsed = puzzle_new(9);

    puzzle_print_simple(parsed, stdout);

    //For testing
    //FILE* file = fopen("parse.txt", "r");
    int k = 0;
    int current;
    while(scanf("%d", &current) == 1) {   
      int i = k/9;
      int j = k%9;
      set_box_val_in_grid(parsed, current, i,j );
      k++;

    }
    printf("\n");
    //parse_user_sudoku(unsolved, parsed, i);
   // i ++;

    //printf("\n\n%s\n\n",parsed );
    //***This needs to be updated to handle string instead of file
    //take the input and build the puzzle struct from the data

    //Print the input
    puzzle_print_simple(parsed, stdout);

    //Solve the sudoku
    //build_sudoku(parsed, mode);
    
    //Print the solved sucdoku
   // puzzle_print_formated(parsed, stdout);



  
  }
  
}

/**************************** bool parse_user_sudoku () **********************************/
/* see sudoku.h for more detail */
bool parse_user_sudoku(FILE* fp, puzzle_t* puzzle, int c)
{ 
  // return NULL if either fp or sudoku is NULL
  if (fp == NULL || puzzle == NULL ){
    printf("something is wrong\n");
    return false;
  }
  
  // scan all sudoku entries and check if they were successfully mathced and assigned
  for (int r = 0; r < 9; r++) 
  {
    //for (int c = 0; c < 9; c++)
    //{
      int value; // store scanned value here
      // check value was  successfully matched and assigned
      int scan_status = fscanf(fp, "%d", &value);
      if(scan_status != 1) return false; 

      // ensure that value is between 0 andf 9 strictly
      if(value <= 9 && value >= 0)
      {
        //create a new box and set its value to be the scanned value, and put it in the sudoku 
        //box_t*  new_box = box_new(9);
        //box_t* original_box
        //set_value(get_box_from_grid(puzzle, r,c), value);
        
        //set_value(new_box, value);

        //set_box_in_grid(puzzle, box, r,c);
      }
      else return false;
    //}
      
      // verify that sudoku  has 9 columns
      //char chr ;
      //fscanf(fp, "%c", &chr);
      //if (r != 8 && chr != '\n')  return false; // if were in the not in the last row and our last character is not \n, 
  }
  // verify that the number of lines in fp is 9 -> 9 rows in sudoku
  //if (lines_in_file(fp) !=9 ) return false; // not  9x9 sudoku

  return true; 
}









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
#include "./library/file.h"
#include "./puzzle/puzzle.h"
#include "./common/build.h"
#include "./common/unique.h"

bool parse_user_sudoku(FILE* fp, puzzle_t* puzzle);

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

  //printf("hi\n");

  //check the mode
  if(strcmp(mode, "create") == 0) {
    
      puzzle_t* puzzle = puzzle_new(9);

    printf("empty puzzle: \n\n");
    puzzle_print_formated(puzzle, stdout);
    printf("\n");

    //build_sudoku(puzzle, mode);
    solve_sudoku(puzzle,0 ,0,difficulty);

    printf("fully  built sudoku: \n\n");
    puzzle_print(puzzle, stdout);
    printf("\n\n");
 

    // delete num  from fully built  sudoku
    //printf("removing entries from puzzle: \n\n");
    //reate_sudoku(puzzle, difficulty);
    //puzzle_print(puzzle, stdout);
    //solve_sudoku(puzzle,0,0,difficulty);
    //printf("solved recursively\n\n");
    //puzzle_print(puzzle, stdout);
    //printf("\n\n");

    // try solving 
    //printf("solving sudoku: ... \n");
    //build_sudoku(puzzle, "solve");
    //puzzle_print_formated(puzzle, stdout);
    //printf("\n\n");
}  
  else { 
        // initialize sudoku to new one
        puzzle_t* parsed = puzzle_new(9);
        // read from stdin
        FILE* file = stdin;
        // try parsing puzzle from stdin
        bool status = parse_user_sudoku(file, parsed);
        

        if (!status)
        {
            fprintf(stderr, "Format Error: Could not parsed puzzle.\n");
            return 3;

        } else{
            printf("Printing parsed puzzle\n\n");
            puzzle_print_formated(parsed, stdout);
            printf("\n\n");
            // solve
            solve_recursively(parsed,0,0,difficulty);
            puzzle_print_formated(parsed, stdout);
            printf("\n\n");
        }
    
    }
}




/**************************** bool parse_user_sudoku () **********************************/
/* see sudoku.h for more detail */
bool parse_user_sudoku(FILE* fp, puzzle_t* puzzle)
{ 
  // return NULL if either fp or sudoku is NULL
  if (fp == NULL || puzzle == NULL ){
    printf("something is wrong\n");
    return false;
  }
    
    
   // store format 
   //char* layout[50];
   char* line;
   int r = -1;
   while((line = freadlinep(fp)) != NULL){
        r++;
        printf("\n%s\n", line);
        free(line);
   }printf("num lines%d\n", r);




// {
// // scan all sudoku entries and check if they were successfully mathced and assigned
//     for (int r = 0; r < 14; r++) 
//     {
//                 //char* str_values; //malloc(16* sizeof(char) + 1); // store scanned value here
//                 // check value was  successfully matched and assigned
//                 char* str_values = freadlinep(fp);
//                 //for
//                 //if(scan_status != 1) return false; 
                

//                 // ensure that value is between 0 andf 9 strictly
//                 if((r != 0 )|| (r!= 4) || (r != 8 )|| (r != 12) || (r != 13)) {

//                     // loop through words in string to check what they are
//                     for(int c = 0; c <= (strlen(str_values)); c++) {
//                         // char* str_values[c = str_values[c];

//                         // set the value of the box at that location  in the puzzle to  the scanned value
//                         if( (strcmp(str_values[c], "|") != 0) || (strcmp(str_values[c], " ") != 0)) { 

//                             if(atoi(str_values[c]) <= get_grid_size(puzzle) && atoi(str_values[c]) >= 0 ) set_value(get_box_from_grid(puzzle, r-1, c-1), atoi(str_values[c]));
//                             }
//                             else if ((r == 5 || r == 6 || r == 7) && (c == 5 || c == 6 || c == 7)) {
//                                 if(atoi(str_values[c]) <= get_grid_size(puzzle) && atoi(str_values[c]) >= 0 ) set_value(get_box_from_grid(puzzle, r-2, c-2), atoi(str_values[c]));
//                             }else if ((r == 9 || r == 10 || r == 11) &&  (r == 9 || r == 10 || r == 11)){
//                                 if(atoi(str_values[c]) <= get_grid_size(puzzle) && atoi(str_values[c]) >= 0 ) set_value(get_box_from_grid(puzzle, r-3, c-3), atoi(str_values[c]));
//                         }
//                         //free(str_values[c]);
//                     }
//                 }

//                 free(str_values); //else return false;
        
//     }free(layout);
//     return true;  

// } 

//return true;
}


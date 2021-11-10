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
#include "./common/build.h"
#include "./common/unique.h"
#include "./library/file.h"


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

  build_sudoku(puzzle, difficulty);

  printf("\n");


  printf("\n");
  //set_value(get_box_from_grid(puzzle, 2 ,3),5);

  //update_all_box_counters(puzzle, 1, 2, 3);

  //solve_sudoku(puzzle);
  puzzle_print(puzzle, stdout);

   
  printf("\n");


  
}



// /**************************** bool parse_user_sudoku () **********************************/
// /* see sudoku.h for more detail */
// bool parse_user_sudoku(FILE* fp, box_t* sudoku[9][9], char* level)
// { 
//   // return NULL if either fp or sudoku is NULL
//   if (fp == NULL || sudoku == NULL ){
//     printf("something is wrong\n");
//     return false;
//   }
  
//   // scan all sudoku entries and check if they were successfully mathced and assigned
//   for (int r = 0; r < 9; r++) 
//   {
//     for (int c = 0; c < 9; c++)
//     {
//       int value; // store scanned value here
//       // check value was  successfully matched and assigned
//       int scan_status = fscanf(fp, "%d", &value);
//       if(scan_status != 1) return false; 

//       // ensure that cvalue is between 0 andf 9 strictly
//       if(value <= 9 && value >= 0)
//       {
//         //create a new box and set its value to be the scanned value, and put it in the sudoku 
//         box_t*  box = box_new();
//         set_value(box, value);
//         sudoku[r][c] = box;
//       }
//       else return false;
//     }
      
//       // verify that sudoku  has 9 columns
//       char chr ;
//       fscanf(fp, "%c", &chr);
//       if (r != 8 && chr != '\n')  return false; // if were in the not in the last row and our last character is not \n, 
//   }
//   // verify that the number of lines in fp is 9 -> 9 rows in sudoku
//   if (lines_in_file(fp) !=9 ) return false; // not  9x9 sudoku

//   // if valid sudoku, return  true
//   return true; 
// }




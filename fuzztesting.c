

/* 
 * fuzzsudoku - generate a series of random sudokus for testing sudoku create and build
 * 
 * usage: 
 *   fuzzquery numSudokus
 *
 * 
 * u
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "./library/memory.h"
#include "./puzzle/puzzle.h"
#include "./create/create.h"
#include "./solve/solve.h"







int
main(const int argc, char *argv[])
{

     
  clock_t start, end;
  double cpu_time_used;
  double total = 0;
     
  //Change the depth string to an integer
  int numSudokus;
  sscanf(argv[1], "%d", &numSudokus);

  for(int i = 1; i <= numSudokus; i ++){


  //Create a full sudoku
  puzzle_t* puzzle = puzzle_new(9);

  char* difficulty = malloc(10 * sizeof(char) + 1);
  strcpy(difficulty, "easy");

  build_full_sudoku(puzzle, difficulty);


  //Create an incomplete sudoku
  create_sudoku(puzzle, difficulty);


  //Solve (and track time)
  
  start = clock();
     
  //solve method
  solve_sudoku(puzzle,0,0,difficulty);

  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  
  total += cpu_time_used;

  printf("Run %d: %f seconds\n", i, cpu_time_used);

  }

  printf("\nAverage run time %f: seconds\n", total/numSudokus);

}

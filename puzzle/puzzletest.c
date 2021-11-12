/*
 * puzzletest.c - unit testing for puzzle.h module
 * 
 * usage: run `make test` on the command line
 * 
 * Dylan Beinstock, Salifyanji Namwila, Veronica Quidore
 * CS50, Prof. Prioleau Fall 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "puzzle.h"


int main() {
    printf("Welcome to the Puzzle Module Unit Tests. We have expected you...\n\n");
	
	printf("try all of the null cases for puzzle_new()\n");
	puzzle_t* puzzbad1 = puzzle_new(-9);
	if (puzzbad1 == NULL) {
		printf("excellent! no memory allocated for invalid (negative) size of puzzle!\n\n");
	} else {
		printf("UNIT TEST FAILED! MEMORY ALLOCATED FOR INVALID PUZZLE SIZE\n\n");
	}

	puzzle_t* puzzbad2 = puzzle_new(7); 
	if (puzzbad2 == NULL) {
		printf("no memory allocated for invalid (non-perfect square) puzzle size! yay! \n\n");
	} else {
		printf("UNIT TEST FAILED! MEMORY ALLOCATED FOR INVALID PUZZLE SIZE\n\n");
	}

	puzzle_t* puzzbad3 = puzzle_new(25);
	if (puzzbad3 == NULL) {
		printf("no memory allocated for invalid (too-large perfect square) puzzle size! yay! \n\n");
	} else {
		printf("UNIT TEST FAILED! MEMORY ALLOCATED FOR INVALID PUZZLE SIZE!!\n\n");
	}

    printf("lets. make. a. PUZZLEEEEEEEEEE\n\n");
    puzzle_t* puzzle1 = puzzle_new(9);
    if (puzzle1 != NULL) {
        printf("memory for puzzle1 successfully allocated!\n\n"); 
        printf("check the initialization of box_t structs within grid indirectly through printing puzzle struct (should be grid of 0s)\n\n");
        puzzle_print_simple(stdout, puzzle1);
        printf("\ngreat! The memory was allocated. we now have puzzle1\n\n");
    } else {
        printf("\nunable to properly allocate memory to puzzle1. UNIT TEST FAILED\n\n");
    }
    
    printf("can we get the grid size...?\n\n");
    int puzzle1_size = get_grid_size(puzzle1);
    if (puzzle1_size == 9) {
        printf("we can get the size of puzzle1! That size is 9\n\n");
    } else {
        printf("get_grid_size() does not work. UNIT TEST FAILED\n\n");
    }

    printf("ok ok ok cool cool cool cool cool, but can we get the actual grid?\n");
    if (get_grid(puzzle1) != NULL) {
        printf("good job! much success! get_grid() works!\n\n");
    } else {
        printf("get_grid() does not work :( UNIT TEST FAILED\n\n");
    }

    printf("Now let's try setting boxes to valid values...\n");
    if (!(set_box_value(puzzle1, 1, 0, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 2, 1, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 3, 2, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 4, 0, 1))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 4, 1, 1))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 6, 2, 1))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 7, 0, 2))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 9, 2, 2))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 4, 3, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 5, 4, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 6, 5, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 7, 6, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 8, 7, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 8, 7, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 9, 8, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 3, 0, 3))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 2, 0, 4))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 5, 0, 5))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 6, 0, 6))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 8, 0, 7))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }
    if (!(set_box_value(puzzle1, 9, 0, 8))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    }

	if (!(set_box_value(puzzle1, 10, 1, 2))) {
		printf("set_box_value() did not assign value to value > puzzle.size... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }

	if (!(set_box_value(puzzle1, 8, 9, 2))) {
		printf("set_box_value() did not assign value when row > coordinate grid index... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }

	if (!(set_box_value(puzzle1, 8, 2, 9))) {
		printf("set_box_value() did not assign alue when column > largest coordinate grid index... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }


    printf("great! First round of numbers set!\n\n");
    
    puzzle_print_simple(stdout, puzzle1);

    printf("now try getting one of the box values\n");
    if ((get_box_value(puzzle1, 2, 0)) != -1) {
        printf("get_box_value() success!\n\n");
    } else {
        printf("get_box_value() did not work. UNIT TEST FAILED!\n\n");
    }

	printf("now try getting a box value at an invalid coordinate\n");
	if ((get_box_value(puzzle1, 9, 9)) == -1) {
		printf("get_box_value() boundary case success!\n\n");
	} else {
		printf("error in get_box_value() boundary case! UNIT TEST FAILED!\n\n");
	}
	
	
    
    printf("well that was nice. Now test how well this baby cross checks the row, column, and 3x3 for existing numbers\n");
    if (!(val_not_in_cross_section(puzzle1, 1, 2, 9))) {
        printf("correct! value was in cross section\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check a different value!\n");
    if (!(val_not_in_cross_section(puzzle1, 1, 2, 7))) {
        printf("correct! value was in cross section\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check a different value!\n");
    if ((val_not_in_cross_section(puzzle1, 1, 2, 8))) {
        printf("correct! value was NOT in cross section\n\n");
    } else {
        printf("unit test failed");
    }

    printf("Test a 4x4 puzzle!!\n\n");
    puzzle_t* puzzle2 = puzzle_new(4);
    if (puzzle2 != NULL) {
        puzzle_print_simple(stdout, puzzle2);
    }

    

    return 0;
}

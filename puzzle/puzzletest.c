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
#include <string.h>
#include <math.h>
#include "puzzle.h"


int main() {
    printf("\nWelcome to the Puzzle Module Unit Tests. We have expected you...\n\n");
	
	printf("try all of the null cases for puzzle_new()\n");
	puzzle_t* puzzbad1 = puzzle_new(-9);
	if (puzzbad1 == NULL) {
		printf("excellent! no memory allocated for invalid (negative) size of puzzle!\n");
	} else {
		printf("UNIT TEST FAILED! MEMORY ALLOCATED FOR INVALID PUZZLE SIZE\n\n");
	}

	puzzle_t* puzzbad2 = puzzle_new(7); 
	if (puzzbad2 == NULL) {
		printf("no memory allocated for invalid (non-perfect square) puzzle size! yay! \n");
	} else {
		printf("UNIT TEST FAILED! MEMORY ALLOCATED FOR INVALID PUZZLE SIZE\n\n");
	}

	puzzle_t* puzzbad3 = puzzle_new(100);
	if (puzzbad3 == NULL) {
		printf("no memory allocated for invalid (too-large perfect square -> 100) puzzle size! yay! \n\n");
	} else {
		printf("UNIT TEST FAILED! MEMORY ALLOCATED FOR INVALID PUZZLE SIZE!!\n\n");
	}

    printf("lets. make. a. PUZZLEEEEEEEEEE (9x9)\n\n");
    puzzle_t* puzzle1 = puzzle_new(9);
    if (puzzle1 != NULL) {
        printf("memory for puzzle1 successfully allocated!\n\n"); 
        printf("check the initialization of box_t structs within grid indirectly through printing puzzle simple and formatted struct (should be grid of 0s)\n\n");
        puzzle_print_simple(stdout, puzzle1);
        puzzle_print_formated(stdout, puzzle1);
        printf("\ngreat! The memory was allocated. we now have puzzle1\n\n");
    } else {
        printf("\nunable to properly allocate memory to puzzle1. UNIT TEST FAILED\n\n");
    }
    
    printf("can we get the grid size...?\n\n");
    int puzzle1_size = get_grid_size(puzzle1);
    if (puzzle1_size == 9) {
        printf("we can get the size of puzzle1! That size is 9\n");
    } else {
        printf("get_grid_size() does not work. UNIT TEST FAILED\n\n");
    }

    int nullpuzzle_size = get_grid_size(NULL);
    if (nullpuzzle_size == -1) {
        printf("did not get size of NULL puzzle! success!\n\n");
    } else {
        printf("got size of NULL puzzle...UNIT TEST FAILED\n\n");
    }

    printf("ok ok ok cool cool cool cool cool, but can we get the actual 2-D grid?\n");
    if (get_grid(puzzle1) != NULL) {
        printf("good job! much success! get_grid() works!\n");
    } else {
        printf("get_grid() does not work :( UNIT TEST FAILED\n");
    }
    if (get_grid(NULL) == NULL) {
        printf("good job! much success! get_grid() returned null on NULL argument!\n\n");
    } else {
        printf("retrieved grid from NULL puzzle :( UNIT TEST FAILED\n\n");
    }

    // valid arguments for set_box_value
    printf("Now let's try setting boxes to valid values...\n");
    if (!(set_box_value(puzzle1, 1, 0, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 2, 1, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 3, 2, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 4, 0, 1))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 4, 1, 1))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 6, 2, 1))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 7, 0, 2))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 9, 2, 2))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 4, 3, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 5, 4, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 6, 5, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 7, 6, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 8, 7, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 8, 7, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 9, 8, 0))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 3, 0, 3))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 2, 0, 4))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 5, 0, 5))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 6, 0, 6))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 8, 0, 7))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if (!(set_box_value(puzzle1, 9, 0, 8))) {
        printf("set_box_value() did not work. UNIT TEST FAILED");
    } else {
        printf("set_box_value() assigned valid value to valid coordinates... SUCCESS\n");
    }
    if ((set_box_value(puzzle1, 0, 2, 8))) {
		printf("set_box_value() did assigned value = 0 for valid coordinates... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }

    // invalid arguments for set_box_value
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
		printf("set_box_value() did not assign value when column > largest coordinate grid index... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }
    if (!(set_box_value(puzzle1, -1, 2, 8))) {
		printf("set_box_value() did not assign value when value < 0 ... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }
    if (!(set_box_value(puzzle1, 2, -2, 8))) {
		printf("set_box_value() did not assign value when x < 0 ... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }
    if (!(set_box_value(puzzle1, 2, 2, -8))) {
		printf("set_box_value() did not assign value when y < 0 ... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }
    if (!(set_box_value(NULL, 0, 2, 8))) {
		printf("set_box_value() did assign value to NULL puzzle... SUCCESS\n");
	} else {
        printf("UNIT TEST FAILED\n\n");
    }
    

    printf("great! First round of numbers set for puzzle1!\n\n");
    
    puzzle_print_simple(stdout, puzzle1);
    puzzle_print_formated(stdout, puzzle1);

    printf("now try getting one of the box values at row 2 column 0\n");
    if ((get_box_value(puzzle1, 2, 0)) != -1) {
        printf("get_box_value() success!\n\n");
    } else {
        printf("get_box_value() did not work. UNIT TEST FAILED!\n\n");
    }

	printf("now try getting a box value at an invalid coordinate (9,9)\n");
	if ((get_box_value(puzzle1, 9, 9)) == -1) {
		printf("get_box_value() boundary case success!\n\n");
	} else {
		printf("error in get_box_value() boundary case! UNIT TEST FAILED!\n\n");
	}
    printf("now try getting a box value with a NULL puzzle\n");
	if ((get_box_value(NULL, 8, 8)) == -1) {
		printf("get_box_value() boundary case success!\n\n");
	} else {
		printf("error in get_box_value() boundary case! UNIT TEST FAILED!\n\n");
	}
    
    printf("well that was nice. Now test how well this baby cross checks the row, column, and 3x3 for existing numbers\n");
    if (!(val_not_in_cross_section(puzzle1, 1, 2, 9))) {
        printf("correct! value 9 was in cross section row 1 column 2\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check a different value!\n");
    if (!(val_not_in_cross_section(puzzle1, 1, 2, 7))) {
        printf("correct! value 7 was in cross section row 1 column 2\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check different coordinates!\n");
    if (!(val_not_in_cross_section(puzzle1, 8, 2, 7))) {
        printf("correct! value (7) was in cross section row = 8, column = 2\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check different coordinates and value!\n");
    if (!(val_not_in_cross_section(puzzle1, 4, 8, 5))) {
        printf("correct! value (5) was in cross section row = 4 column = 8\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check a different value!\n");
    if ((val_not_in_cross_section(puzzle1, 1, 2, 8))) {
        printf("correct! value 8 was NOT in cross section row = 1 column = 2\n\n");
    } else {
        printf("unit test failed");
    }
    printf("check a NULL puzzle!\n");
    if ((val_not_in_cross_section(NULL, 1, 2, 8))) {
        printf("correct! returned true upon NULL puzzle\n\n");
    } else {
        printf("unit test failed");
    }

    printf("check is_val_in_box()...\n");
    if (!(is_val_in_box(puzzle1, 0, 2, 2, 3))) {
        printf("success! correctly detected 3 is in 3x3 box for row 2 column 2\n");
    } else {
        printf("UNIT TEST FAILED\n\n");
    }
    if ((is_val_in_box(puzzle1, 3, 3, 2, 3))) {
        printf("success! correctly detected 3 is in 3x3 box for row 2 column 3\n");
    } else {
        printf("UNIT TEST FAILED\n\n");
    }
    if ((is_val_in_box(NULL, 3, 3, 2, 3))) {
        printf("success! correctly returned true for NULL puzzle argument\n");
    } else {
        printf("UNIT TEST FAILED\n\n");
    }

    printf("test NULL file pointers for print methods (should get error msgs)\n");
    puzzle_print_simple(NULL, puzzle1);
    puzzle_print_formated(NULL, puzzle1);

    printf("test NULL puzzle for print methods (should print (null) )\n");
    puzzle_print_simple(stdout, NULL);
    puzzle_print_formated(stdout, NULL);
    printf("\n");

    // NULL boundary cases were already tested on 9x9
    // test cases for different sizes will check if getter and setter ranges are dynamic

    printf("Make a 25x25 puzzle!!\n\n");
    puzzle_t* puzzle2 = puzzle_new(25);
    if (puzzle2 != NULL) {
        puzzle_print_simple(stdout, puzzle2);
        puzzle_print_formated(stdout, puzzle2);
    } else {
        printf("memory failed to allocate for 25x25 puzzle struct... UNIT TEST FAILED\n\n");
    }

    printf("set a few numbers.. \n");
    if ((set_box_value(puzzle2, 25, 4, 4))) {
        printf("success! 25 set at (4,4)\n");
    }
    if ((set_box_value(puzzle2, 4, 24, 24))) {
        printf("success! 4 set at (24,24)\n");
    } 
    if (!(set_box_value(puzzle2, 26, 24, 24))) {
        printf("success! 26 NOT set at (24,24)\n");
    } 
    if (!(set_box_value(puzzle2, 4, 24, 25))) {
        printf("success! 4 NOT set at (24,25)\n");
    } 
    if (!(set_box_value(puzzle2, 4, 25, 24))) {
        printf("success! 4 set at (25,24)\n\n");
    } 

    printf("check getters...\n");
    int puzzle2_size = get_grid_size(puzzle2);
    printf("puzzle2_size is %d\n\n", puzzle2_size);

    if (get_box_value(puzzle2, 24, 24) != -1) {
        printf("success! retrieved puzzle2 (24,24) value as %d\n", get_box_value(puzzle2, 24, 24));
    }
    if (get_box_value(puzzle2, 25, 24) == -1) {
        printf("success! retrieved puzzle2 (25,24) value as %d\n", get_box_value(puzzle2, 25, 24));
    }
    if (get_box_value(puzzle2, 24, 25) == -1) {
        printf("success! retrieved puzzle2 (24,25) value as %d\n\n", get_box_value(puzzle2, 24, 25));
    }

    printf("check cross-sectional validation in puzzle2\n");
    if (!(val_not_in_cross_section(puzzle2, 23, 22, 4))) {
        printf("correct! 4 is in cross section of point (23, 22)\n");
    }
    if (!(val_not_in_cross_section(puzzle2, 19, 24, 4))) {
        printf("correct! 4 is in cross section of point (19, 24)\n");
    }
    if (!(val_not_in_cross_section(puzzle2, 24, 12, 4))) {
        printf("correct! 4 is in cross section of point (24, 12)\n");
    }
    if ((val_not_in_cross_section(puzzle2, 24, 12, 7))) {
        printf("correct! 7 is NOT in cross section of point (24, 12)\n\n");
    }

    printf("Make a 36x36 puzzle!!\n\n");
    puzzle_t* puzzle3 = puzzle_new(36);
    if (puzzle3 != NULL) {
        puzzle_print_simple(stdout, puzzle3);
        puzzle_print_formated(stdout, puzzle3);
    } else {
        printf("memory failed to allocate for 25x25 puzzle struct... UNIT TEST FAILED\n\n");
    }


    printf("Make a 16x16 puzzle!!\n\n");
    puzzle_t* puzzle4 = puzzle_new(16);
    if (puzzle4 != NULL) {
        puzzle_print_simple(stdout, puzzle4);
        puzzle_print_formated(stdout, puzzle4);
    } else {
        printf("memory failed to allocate for 25x25 puzzle struct... UNIT TEST FAILED\n\n");
    }

    printf("Make a 4x4 puzzle!!\n\n");
    puzzle_t* puzzle5 = puzzle_new(4);
    if (puzzle5 != NULL) {
        puzzle_print_simple(stdout, puzzle5);
        puzzle_print_formated(stdout, puzzle5);
    } else {
        printf("memory failed to allocate for 25x25 puzzle struct... UNIT TEST FAILED\n\n");
    }

    printf("set a few numbers.. \n");
    if ((set_box_value(puzzle5, 0, 3, 3))) {
        printf("success! 0 set at (3,3)\n");
    }
    if ((set_box_value(puzzle5, 4, 3, 3))) {
        printf("success! 4 set at (3,3)\n");
    } 
    if ((set_box_value(puzzle5, 3, 2, 1))) {
        printf("success! 3 set at (1,2)\n");
    }
    if (!(set_box_value(puzzle5, 5, 3, 2))) {
        printf("success! 5 NOT set at (2,3)\n\n");
    } 

    printf("check getters...\n");
    int puzzle5_size = get_grid_size(puzzle5);
    printf("puzzle2_size is %d\n\n", puzzle5_size);

    if (get_box_value(puzzle5, 2, 1) != -1) {
        printf("success! retrieved puzzle2 (24,24) value as %d\n", get_box_value(puzzle5, 2, 1));
    }
    if ((get_box_value(puzzle5, 3, 4)) == -1) {
        printf("success! retrieved puzzle2 (25,24) value as %d\n", get_box_value(puzzle5, 3, 4));
    }
    printf("check cross-sectional validation in puzzle2\n");
    puzzle_print_simple(stdout, puzzle5);
    if (!(val_not_in_cross_section(puzzle5, 2, 3, 4))) {
        printf("correct! 4 is in cross section of point (2,3)\n");
    }
    if ((val_not_in_cross_section(puzzle2, 1,0, 4))) {
        printf("correct! 4 is NOT in cross section of point (1,0)\n");
    }

    printf("check get_num_to_delete() method\n\n");
    char* easy_level = count_calloc_assert(5, sizeof(char), "EY CANT CALLOC StrING Here WHAY\n");
    strcpy(easy_level, "easy");
    char* hard_level = count_calloc_assert(5, sizeof(char), "EY CANT CALLOC StrING Here WHAY\n");
    strcpy(hard_level, "hard");
    char* medium_level = count_calloc_assert(7, sizeof(char), "EY CANT CALLOC StrING Here WHAY\n");
    strcpy(medium_level, "medium");

    int size9_easy = get_num_todelete(puzzle1, easy_level);
    printf("for puzzle size 9 level easy get %d to delete\n", size9_easy);
    int size9_hard = get_num_todelete(puzzle1, hard_level);
    printf("for puzzle size 9 level hard get %d to delete\n", size9_hard);
    int size9_medium = get_num_todelete(puzzle1, medium_level);
    printf("for puzzle size 9 level medium get %d to delete\n", size9_medium);
    int sizeNULL_easy = get_num_todelete(NULL, easy_level);
    printf("for puzzle size NULL level easy get %d to delete\n", sizeNULL_easy);
    
    int size16_easy = get_num_todelete(puzzle4, easy_level);
    printf("for puzzle size 16 level easy get %d to delete\n", size16_easy);
    int size16_hard = get_num_todelete(puzzle4, hard_level);
    printf("for puzzle size 16 level easy get %d to delete\n", size16_hard);
    int size16_medium = get_num_todelete(puzzle4, medium_level);
    printf("for puzzle size 16 level easy get %d to delete\n\n", size16_medium);

    count_free(easy_level);
    count_free(medium_level);
    count_free(hard_level);

    printf("test the is_valid_solved() and is_valid_unsolved() methods\n");
    if (!(is_valid_solved(NULL)) && !(is_valid_unsolved(NULL))) {
        printf("returned false w/o seg faults for NULL puzzle args in methods! Final SUCCESS!\n\n");
    }

    printf("deleting puzzles...\n\n");
    puzzle_delete(puzzle1);
    puzzle_delete(puzzle2);
    puzzle_delete(puzzle3);
    puzzle_delete(puzzle4);
    puzzle_delete(puzzle5);
    printf("puzzles deleted!\n\n");
    
    printf("end of unit testing! thank you and goodbye!\n\n\n");
    return 0;
}


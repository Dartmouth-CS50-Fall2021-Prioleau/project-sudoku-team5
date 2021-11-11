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

    printf("lets. make. a. PUZZLEEEEEEEEEE\n\n");
    puzzle_t* puzzle1 = puzzle_new(9);
    if (puzzle1 != NULL) {
        printf("memory for puzzle1 successfully allocated!\n\n"); 
        printf("check the initialization of box_t structs within grid indirectly through printing puzzle struct (should be grid of 0s)\n");
        puzzle_print_simple(puzzle1, stdout);
        printf("great! The memory was allocated. we now have puzzle1\n\n");
    } else {
        printf("unable to properly allocate memory to puzzle1. UNIT TEST FAILED\n\n");
    }
    
    printf("can we get the grid size...?\n");
    int puzzle1_size = get_grid_size(puzzle1);
    if (puzzle1_size == 9) {
        printf("we can get the size of puzzle1! That size is 9\n\n");
    } else {
        printf("get_grid_size() does not work. UNIT TEST FAILED\n\n");
    }

    printf("Now let's try setting the values...\n");
    set_box_val_in_grid(puzzle1, 1, 0, 0);
    set_box_val_in_grid(puzzle1, 2, 1, 0);
    set_box_val_in_grid(puzzle1, 3, 2, 0);
    set_box_val_in_grid(puzzle1, 4, 0, 1);
    set_box_val_in_grid(puzzle1, 4, 1, 1);
    set_box_val_in_grid(puzzle1, 6, 2, 1);
    set_box_val_in_grid(puzzle1, 7, 0, 2);
    set_box_val_in_grid(puzzle1, 8, 1, 2);
    set_box_val_in_grid(puzzle1, 9, 2, 2);
    puzzle_print_simple(puzzle1, stdout);
    
    set_box_val_in_grid(puzzle1, 4, 3, 0);
    set_box_val_in_grid(puzzle1, 5, 4, 0);
    set_box_val_in_grid(puzzle1, 6, 5, 0);
    set_box_val_in_grid(puzzle1, 7, 6, 0);
    set_box_val_in_grid(puzzle1, 8, 7, 0);
    set_box_val_in_grid(puzzle1, 9, 8, 0);
    puzzle_print_simple(puzzle1, stdout);

    set_box_val_in_grid(puzzle1, 3, 0, 3);
    set_box_val_in_grid(puzzle1, 2, 0, 4);
    set_box_val_in_grid(puzzle1, 5, 0, 5);
    set_box_val_in_grid(puzzle1, 6, 0, 6);
    set_box_val_in_grid(puzzle1, 8, 0, 7);
    set_box_val_in_grid(puzzle1, 9, 0, 8);
    puzzle_print_simple(puzzle1, stdout);

    int test = get_box_val_from_grid(puzzle1, 2, 0);
    printf("\n%d\n", test);

    if ((val_not_in_cross_section(puzzle1, 1, 1, 9)) == false) {
        printf("unit test succeeded!\n");
    } else {
        printf("unit test failed");
    }


    return 0;
}

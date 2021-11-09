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
#include "puzzle.h"
#include "../box/box.h"


int main() {
    printf("Welcome to the Puzzle Module Unit Tests. We have expected you...\n\n");

    printf("lets. make. a. PUZZLEEEEEEEEEE\n\n");
    puzzle_t* puzzle1 = puzzle_new(36);
    if (puzzle1 != NULL) {
        printf("memory for puzzle1 successfully allocated!\n\n"); 
        printf("check the initialization of box_t structs within grid indirectly through printing puzzle struct (should be grid of 0s)\n");
        puzzle_print(puzzle1, stdout);
    } else {
        printf("unable to properly allocate memory to puzzle1. UNIT TEST FAILED\n\n");
    }

    return 0;
}

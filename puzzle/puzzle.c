#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../box/box.h"
#include "../library/memory.h"

/**************** file-local global variables ****************/
/* none */


/**************** global types ****************/
typedef struct puzzle {
    int size;
    box_t* grid;
} puzzle_t;

puzzle_t* puzzle_new(int size, box_t* board[9][9]) {

    // int size_squared = size * size;
    puzzle_t* puzzle = count_malloc((sizeof(puzzle_t)));
    if (puzzle != NULL) {
        puzzle->size = size;
        puzzle->grid = board;
        // algorithm from geeks4geeks
        //box_t** grid = count_calloc(size_squared, sizeof(box_t*));
        if (puzzle->grid != NULL) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {  // needs to be revised

                    //box_t* box = box_new();
                    box_t* grid[9][9] = puzzle->grid;
                    grid[i][j] = count_malloc(sizeof(box_t*));
                    grid[i][j] = box_new();
                }
            }  
            return puzzle;
        }
        return NULL;
    }
    return NULL;
}

box_t** get_grid(puzzle_t* puzzle) {

    if (puzzle != NULL && puzzle->grid != NULL) {
        return puzzle->grid;
    }
    return NULL;
}

box_t* get_box_from_grid(puzzle_t* puzzle, int x, int y) {

    if ((puzzle != NULL && puzzle->grid != NULL) && ((x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size))) {
        box_t* grid[9][9] = puzzle->grid;
        box_t* box = grid[x][y];
        return box;
    }
    return NULL;
}

void set_box_in_grid(puzzle_t* puzzle, box_t* box, int x, int y)
{
    if (puzzle != NULL && puzzle->grid != NULL && box != NULL && (x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size)) {
        box_t* grid[9][9] = puzzle->grid;
        grid[x][y] = box;
    }
}

int get_grid_size(puzzle_t* puzzle)
{
    if (puzzle != NULL && puzzle->grid != NULL) {
        return puzzle->size;
    }
}


void puzzle_delete(puzzle_t* puzzle)
{
    for (int i = 0; i < puzzle->size; i++) {
        for (int j = 0; j < puzzle->size; j++) {
            box_t* grid[9][9] = puzzle->grid;
            box_t* box = grid[i][j];
            box_delete(box);
        }
    }

    if (puzzle != NULL) {
        count_free(puzzle);
    }
}


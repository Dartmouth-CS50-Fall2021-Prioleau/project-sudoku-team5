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

void update_adjacent_box_counters(box_t* sudoku[9][9], int x, int y, int value) {
    // to do
    
    for (int i = 0; i < 9; i++) { // for column of current box
        // if cross sectional val is 0, proceed, otherwise skip
        counters_t* column_count = get_counter(sudoku[x][i]);
        int availability = counters_get(column_count, value);
        if (availability == 1) {
            counters_set(column_count, value, 0);
        }
    }

    for (int j = 0; j < 9; j++) {
        counters_t* row_count = get_counter(sudoku[j][y]);
        int availability = counters_get(row_count, value);
        if (availability == 1) {
            counters_set(row_count, value, 0);
        }
    }

    int m, n;

    if (x % 3 == 1) { m = -1; }
    else if (x % 3 == 2) { m = -2; }
    else { m = 0; }

    if (y % 3 == 1) { n = -1; }
    else if (y % 3 == 2) { n = -2; }
    else { n = 0; }

    for ( ; m < 3 - (x%3); m++) {
        for ( ; n < 3 - (y%3); n++) {
            if ((x + m != x) || (y + n != y)) {
                int neighbor_x = x + m;
                int neighbor_y = y + n;
                counters_t* three_three_count = get_counter(sudoku[neighbor_x][neighbor_y]);
                int availability = counters_get(three_three_count, value);
                if (availability == 1) {
                    counters_set(three_three_count, value, 0);
                }
            }
        }
    }
}


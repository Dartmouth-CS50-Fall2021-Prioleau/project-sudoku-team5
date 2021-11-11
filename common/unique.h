
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "../library/counters.h"
#include "../puzzle/puzzle.h"

#ifndef __UNQIUE_H
#define __UNIQUE_H


/************************ global fucntions *********************/
int count_num_solutions(puzzle_t* puzzle, char* level);
bool val_not_in_cross_section(puzzle_t* puzzle, int row, int column, int value, char* level);


#endif // __UNIQUE_H
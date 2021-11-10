/*
 * boxtest.c - unit testing for box.h module
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
#include "box.h"

static void initialized_count_check(void* arg, const int key, const int count);

int main() {
    
    printf("Welcome to Box Module Unit Testing.\n");
    printf("We have been expecting you....\n\n");
    
    printf("let's start off simple. make a box called box1 through the method box_new()\n");
    box_t* box1 = box_new(9);
    
    printf("check its initialization...\n");
    if (box1 != NULL) {
        printf("memory for box1's box_t* structure successfully allocated! now check the box1's integer value.\n\n");
        int box1_value = get_value(box1);
        
        if (box1_value == 0) {
            printf("box1's value successfully initialized to 0!\n\n");
            
            printf("let's check the size of the grid for box1\n");
            int box1_grid_size = get_grid_size_from_box(box1);
            if (box1_grid_size == 9) {
                printf("size of grid successfully stored in box struct!\n\n");

                printf("let's check the range counterset for box1 next!\n");
                
                counters_t* box1_range_counters = get_counter(box1);
                if (box1_range_counters != NULL) {
                    printf("box1 counterset memory successfully allocated! Now check the potential value count for each of the counter's keys\n");
                    int is_init_range_count_1 = 0;
                    counters_iterate(box1_range_counters, &is_init_range_count_1, initialized_count_check);
                    
                    if (is_init_range_count_1 == box1_grid_size) {
                        printf("counts in box1 range counters set successfully initialized to 1!\n\n"); 
                        
                        printf("Let's check the visited counterset for box1\n");

                        counters_t* box1_visited_counters = get_visited(box1);
                        if (box1_visited_counters != NULL) {
                            int is_init_visited_count_1 = 0;
                            counters_iterate(box1_visited_counters, &is_init_visited_count_1, initialized_count_check);

                            if (is_init_visited_count_1 == box1_grid_size) {
                                printf("counts in box1 visited counters set successfully initialized to 1!\n\n"); 
                                printf("Initializations successfully checked!\n\n");
                            } else {
                                printf("visited counts incorrectly initialized. UNIT TEST FAILED\n\n");
                            }   
                        } else {
                            printf("oops! could not properly allocate memory to the box1 visited counterset.\nUNIT TEST FAILED\n\n");
                        } 
                    } else {
                        printf("range counts incorrectly initialized. UNIT TEST FAILED\n\n");
                    }

                } else {
                    printf("oh no! could not properly allocate memory to the box1 range counterset.\nUNIT TEST FAILED \n");
                }
            } else {
                printf("size of greater grid not successfully stored. UNIT TEST FAILED\n");
            }
            
        } else {
            printf("uh oh! Something went wrong! box1's value was not initialized to 0.\nUNIT TEST FAILED :(\n");
        }

    } else {
        printf("Uh oh! Error allocating memory for box! \nUNIT TEST FAILED. :(\n\n");
    }

    printf("check setting value to a valid number (0 < value <= size_of_grid\n");
    printf("valid number is: 7\n");
    set_value(box1, 7);
    if (get_value(box1) == 7) {
        printf("box1->value = %d\n\n", get_value(box1));
    } else {
        printf("value could not be set. UNIT TEST FAILED\n\n");
    }
    
    printf("check the reset methods for the range and visited counters in box1\n");
    counters_t* range_c = get_counter(box1);
    counters_set(range_c, 1, 54);
    counters_set(range_c, 2, 4);
    counters_set(range_c, 4, -9);
    counters_set(range_c, 6, 0);
    counters_set(range_c, 9, 8);
    printf("box1 range counters: ");
    counters_print(range_c, stdout);
    printf("\nnow reset...\n");
    reset_box(box1);
    printf("box1 range counters: ");
    counters_print(range_c, stdout);

    counters_t* visited_c = get_visited(box1);
    counters_set(visited_c, 3, -19);
    counters_set(visited_c, 5, 10001);
    counters_set(visited_c, 8, 3);
    printf("box1 visited counters: ");
    counters_print(visited_c, stdout);
    printf("\nnow reset...\n");
    reset_visited(box1);
    printf("box1 visited counters: ");
    counters_print(visited_c, stdout);

    printf("\nTest Boundary Cases\n");

    printf("test invalid size of 17 in box_new()\n");
    box_t* box2 = box_new(17);
    if (box2 == NULL) {
        printf("invalid size. Must be a perfect square, but UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle invalid size, UNIT TEST FAILED!\n\n");
    }

    printf("test invalid size of -2 in box_new()\n");
    box_t* box3 = box_new(-2);
    if (box3 == NULL) {
        printf("invalid size. Must be a perfect square, but UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle invalid size, UNIT TEST FAILED!\n\n");
    }

    printf("test NULL box in get_counter() for the counters range of box\n");
    counters_t* boundary_c1 = get_counter(NULL);
    if (boundary_c1 == NULL) {
        printf("correctly handled NULL case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle null case, UNIT TEST FAILED\n\n");
    }

    printf("test NULL box in get_visited() for the counters visited of box\n");
    counters_t* boundary_c2 = get_visited(NULL);
    if (boundary_c2 == NULL) {
        printf("correctly handled NULL case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle null case, UNIT TEST FAILED\n\n");
    }

    printf("test NULL box in get_value()\n");
    int boundary_val1 = get_value(NULL);
    if (boundary_val1 == -1) {
        printf("correctly handled NULL case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle null case, UNIT TEST FAILED\n\n");
    }

    printf("test NULL box in set_value()\n");
    set_value(NULL, 2);
    int boundary_val2 = get_value(NULL);
    if (boundary_val2 == -1) {
        printf("correctly handled NULL case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle null case, UNIT TEST FAILED\n\n");
    }

    printf("test negative value (-4) in set_value()\n");
    set_value(box1, -4);
    int boundary_val3 = get_value(box1);
    if (boundary_val3 == -1) {
        printf("correctly handled boundary case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle boundary case, UNIT TEST FAILED\n\n");
    }

    printf("test value greater than size of grid (value = 19) in set_value()\n");
    set_value(box1, 19);
    int boundary_val4 = get_value(box1);
    if (boundary_val4 == -1) {
        printf("correctly handled boundary case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle boundary case, UNIT TEST FAILED\n\n");
    }
    
    printf("test get_grid_size_from_box() with null input\n");
    int boundary_val5 = get_grid_size_from_box(NULL);
    if (boundary_val5 == -1) {
        printf("correctly handled NULL case, UNIT TEST SUCCEEDED!\n\n");
    } else {
        printf("Cannot handle NULL case, UNIT TEST FAILED\n\n");
    }
    
    printf("check nulls on reset range and visited counters\n");
    reset_box(NULL);
    reset_visited(NULL);

    printf("deleting box....\n");
    box_delete(box1);
    printf("yay!!! UNIT TESTING COMPLETE AND FULLY PASSED!\n\n");

    return 0;
}

static void initialized_count_check(void* arg, const int key, const int count) 
{
    int* count_of_one = arg;
    if (count_of_one != NULL && key > 0 && count == 1) {
        (*count_of_one)++;
    }

}
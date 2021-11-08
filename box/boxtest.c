/*
 *
 *
 * 
 * 
 * 
 * 
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

                printf("let's check the counterset for box1 next!\n");
                
                counters_t* box1_counters = get_counter(box1);
                if (box1_counters != NULL) {
                    print("box1 counterset memory successfully allocated! Now check the potential value count for each of the counters keys\n");
                    int is_init_count_1 = 0;
                    counters_iterate(box1_counters, &is_init_count_1, initialized_count_check);
                    
                    if (is_init_count_1 == box1_grid_size) {
                        printf("counts in box1 counters set successfully initialized to 1!\n"); 
                        printf("Initializations successfully checked!\n\n");
                    } else {
                        printf("counts incorrectly initialized. UNIT TEST FAILED\n\n");
                    }

                } else {
                    printf("oh no! could not properly allocate memory to the box1 counterset.\nUNIT TEST FAILED \n");
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
    
    
    return 0;
}

static void initialized_count_check(void* arg, const int key, const int count) 
{
    int* count_of_one = arg;
    if (count_of_one != NULL && key > 0 && count == 1) {
        (*count_of_one)++;
    }

}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../box/box.h"
#include "../library/memory.h"
#include <string.h>

/**************** file-local global variables ****************/
/* none */


/**************** global types ****************/
typedef struct puzzle 
{
    int size;
    box_t*** grid;
}puzzle_t;






puzzle_t* puzzle_new(int size) {

    // int size_squared = size * size;
    puzzle_t* puzzle = count_malloc((sizeof(puzzle_t)));
    if (puzzle != NULL) {
        puzzle->size = size;
        double sqrt_size = sqrt(size);
        if ((ceil(sqrt_size) == floor(sqrt_size)) && size > 0) {  // check for perfect square
            box_t*** grid = count_calloc_assert(size, sizeof(box_t***), "GRID IS NULL OH NO\n");
            if (grid != NULL) {
                puzzle->grid = grid;
                for (int i = 0; i < size; i++) {
                    box_t** row_holder = count_calloc_assert(size, sizeof(box_t**), "ROW-HOLDER IS NULL OH NO\n");
                    grid[i] = row_holder;
                    for (int j = 0; j < size; j++) {  // needs to be revised
                        grid[i][j] = count_malloc(sizeof(box_t*));
                        grid[i][j] = box_new(size);
                    }
                }  
                return puzzle;
            }
        }
        
        return NULL;
    }
    return NULL;
}





box_t* get_box_from_grid(puzzle_t* puzzle, int x, int y) {

    if ((puzzle != NULL && puzzle->grid != NULL) && ((x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size))) {
        //box_t* grid[9][9] = puzzle->grid;
        box_t* box = puzzle->grid[x][y];
        return box;
    }
    return NULL;
}





void set_box_in_grid(puzzle_t* puzzle, box_t* box, int x, int y)
{
    if (puzzle != NULL && puzzle->grid != NULL && box != NULL && (x > -1 && x < puzzle->size) && (y > -1 && y < puzzle->size)) {
        //box_t* grid[9][9] = puzzle->grid;
        puzzle->grid[x][y] = box;
    }
}






int get_grid_size(puzzle_t* puzzle)
{
    if (puzzle != NULL && puzzle->grid != NULL) {
        return puzzle->size;
    }
    return -1;
}





int get_box_value(puzzle_t* puzzle,int  x, int y)
{   
  
  return get_value(puzzle->grid[x][y]);

}




int get_box_count(puzzle_t* puzzle,int x, int y, int value)
{   
  
  return counters_get(get_counter(puzzle->grid[x][y]), value);

}



int get_visit_count(puzzle_t* puzzle,int  x, int y, int value){

  return counters_get(get_visited(puzzle->grid[x][y]), value );


}




void puzzle_delete(puzzle_t* puzzle)
{
    if (puzzle->grid != NULL) {
        for (int i = 0; i < puzzle->size; i++) {
            if (puzzle->grid[i] != NULL) {
                for (int j = 0; j < puzzle->size; j++) {
                    if (puzzle->grid[i][j] != NULL) {
                        box_t* box = puzzle->grid[i][j];
                        box_delete(box);
                    }
                    //box_t* grid[9][9] = puzzle->grid;
                    //box_t* box = puzzle->grid[i][j];
                    //box_delete(box);
                }
                count_free(puzzle->grid[i]);
            }
            
            
        }
    }
    
    
    if (puzzle != NULL) {
        count_free(puzzle);
    }
}






void puzzle_print (puzzle_t* puzzle, FILE* fp)
{
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(puzzle->grid == NULL){
        printf("(null)");
        return;
    }

    for( int i = 0; i < puzzle->size; i++){  // row
        for(int j= 0 ; j < puzzle->size; j++){  // column
           box_value_print(puzzle->grid[i][j],fp); 
        }
        printf("\n"); // print next row of sudoku
    }

}





void update_adjacent_box_counters(puzzle_t* puzzle, int x, int y, int value) 
{

    for (int i = 0; i < 9; i++) { // for column of current box
        // if cross sectional val is 0, proceed, otherwise skip
        
        counters_t* column_count = get_counter(puzzle->grid[x][i]);
        int availability = counters_get(column_count, value);
        if (availability == 1) {
          
            counters_set(column_count, value, 0);
        }
    }

    for (int j = 0; j < 9; j++) {
        counters_t* row_count = get_counter(puzzle->grid[j][y]);
        int availability = counters_get(row_count, value);
        if (availability == 1) {
            counters_set(row_count, value, 0);
        }
    }

    int a;
    int b;

    if (x % 3 == 1) { a = -1; }
    else if (x % 3 == 2) { a = -2; }
    else { a = 0; }

    if (y % 3 == 1) { b = -1; }
    else if (y % 3 == 2) { b = -2; }
    else { b = 0; }

    for (int m = a; m < 3 - (x%3) ; m += 1) {
        for (int n = b ; n < 3 - (y%3) ; n++) { 
            //if ((x + m != x) || (y + n != y)) {
              
                int neighbor_x = x + m;
                int neighbor_y = y + n;

                //printf("%d, %d, %d %d %d %d\n", x, y,neighbor_x, neighbor_y, m ,n);
                counters_t* three_three_count = get_counter(puzzle->grid[neighbor_x][neighbor_y]);
                int availability = counters_get(three_three_count, value);
                if (availability == 1) {

                    counters_set(three_three_count, value, 0);
                }
            //}
        }
    }
}





void update_all_box_counters(puzzle_t* puzzle) 
{

  for(int i = 0; i < 9; i ++) {
    for(int j = 0; j < 9; j ++) {

      int v = get_value(puzzle->grid[i][j]);

      if(v != 0){ 

        update_adjacent_box_counters(puzzle,i,j,v); 

        
        }

      }
    }
}





void reset_all(puzzle_t* puzzle) 
{

    for(int i = 0; i < 9; i ++) {
      for(int j = 0; j < 9; j ++) {
        reset_box(puzzle->grid[i][j]);
      }
    }  
}





/*****************************************/
/************Printing Methods*************/
/*****************************************/

void puzzle_print_simple (puzzle_t* puzzle, FILE* fp)
{
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(puzzle->grid == NULL){
        printf("(null)");
        return;
    }

    for( int i = 0; i < 9; i++){  // row
        for(int j= 0 ;j < 9; j++){  // column
           box_value_print(puzzle->grid[i][j],fp); 
        }
        printf("\n"); // print next row of sudoku
    }

}



void puzzle_print_formated (puzzle_t* puzzle, FILE* fp)
{
    // handle NULL sudoku
    if(fp == NULL){ 
        return;
    }
    // print null if sudoku is null
    if(puzzle == NULL){
        printf("(null)");
        return;
    }


    printf("+-------+-------+-------+\n");
     
    // the  3 3X3 sudoku's in the first row
    for ( int i = 0; i< 3; i++){  //first three rows

        for(int j= 0 ;j < 9; j++){ // all their collumns

            // start of column
            if(  j == 0 ){
                printf("| ");
                box_value_print(puzzle->grid[i][j],fp);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 box_value_print(puzzle->grid[i][j],fp);
                 printf("| ");
             }
             else if ( j == 8){
                 //print vertical bound
                 box_value_print(puzzle->grid[i][j],fp);
                 printf("|");
             }
            else{
                box_value_print(puzzle->grid[i][j],fp); 
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");


    // the  3 3X3 sudoku's in the second row
    for ( int i = 3; i< 6; i++){

        for(int j= 0 ;j < 9; j++){

            // start of column
            if(  j == 0 ){
                printf("| ");
                box_value_print(puzzle->grid[i][j],fp);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 box_value_print(puzzle->grid[i][j],fp);
                 printf("| ");
             }
            else{
                box_value_print(puzzle->grid[i][j],fp); 
            }
        }printf("\n"); // print next row of sudoku
       

    } printf("+-------+-------+-------+\n");



    // the  3 3X3 sudoku's in the third(last) row
    for ( int i = 6; i< 9; i++){  // last three rows

        for(int j= 0 ;j < 9; j++){ // all their columns

            // start of column
            if(  j == 0 ){
                printf("| ");
                box_value_print(puzzle->grid[i][j],fp);
            }

             // end of sub 3X3 sudoku
             else if ( j  == 2 || j == 5 || j == 8){
                 //print vertical bound
                 box_value_print(puzzle->grid[i][j],fp);
                 printf("| ");
             }
            else{
                box_value_print(puzzle->grid[i][j],fp); 
            }
        }printf("\n"); // print next row of sudoku     
    } printf("+-------+-------+-------+\n"); // of sudoku line
}

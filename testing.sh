#!/bin/bash 
# Testing script for sudoku.c
# Authors: Dylan Beinstock, Salifyanji J. Namwila, and Veronica Quidore
# Date: November 11 2021
#
# usage: bash -v testing.sh

############################################
### Tests with invalid arguements ###

# 1 argument
./sudoku 

# 2 argument
./sudoku create

# 2 argument with invalid mode
./sudoku invalid_mode

# 3 argument with invalid mode
./sudoku invalid_mode easy

# 3 argument with invalid difficulty
./sudoku create invalid_difficulty

# 4 argument with invalid size
./sudoku create easy 5

############################################
### Tests with invalid solve arguements ###

# solve that breaks sudoku rules
cat testing_files/invalid_sudoku.txt | ./sudoku solve

# solve less than 25 given numbers 
cat testing_files/less_25_numbers.txt | ./sudoku solve

# solve with too few inputs
cat testing_files/too_few_inputs.txt | ./sudoku solve

# solve with too many inputss
cat testing_files/too_many_inputs.txt | ./sudoku solve


############################################
#####   Tests with Valid arguements   ######

# Create and Solve easy
./sudoku create easy | ./sudoku solve easy

sleep 2

# Create and Solve hard
./sudoku create hard | ./sudoku solve hard

sleep 2

#Solve with 2 arguments 
./sudoku create easy | ./sudoku solve

sleep 2

#Solve a known solution and compare to the solution
cat testing_files/sudoku_1_input.txt | ./sudoku solve > testing_files/sudoku_1_output.txt

if diff testing_files/sudoku_1_output.txt testing_files/sudoku_1_solution.txt
then 
    echo "Sudoku files are the same"
else 
    echo "Sudoku files are different"
fi



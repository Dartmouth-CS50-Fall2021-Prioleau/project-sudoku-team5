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


############################################
#####   Tests with Valid arguements   #######

# Create and Solve easy
./sudoku create easy | ./sudoku solve easy

# Create and Solve hard
./sudoku create easy | ./sudoku solve easy

#Solve with 2 arguments 
./sudoku create easy | ./sudoku solve



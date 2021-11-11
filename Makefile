# Makefile for 'sudoku' module
#
# CS50 Fall 2021 Sudoku Projct  -Sudoku
# Authors:  Dylan Beinstock, Salifyanji J Namwila, Veronica Quidore
#
# Date: November 3, 2021
#
# Based on Makefile for bags module by:
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Temi Prioleau, January 2020



#Outside libraries
L = ./library
C = ./create
B = ./box
P = ./puzzle
M = ./common


CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C -I$B -I$P -I$M
CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

OBJS = $L/counters.o $C/create.o $B/box.o $L/memory.o $L/file.o $P/puzzle.o  $M/unique.o 

LIBS = -lm

sudoku: sudoku.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


# Dependencies: object files depend on header files
sudoku.o: $L/counters.h $C/create.h $B/box.h $L/memory.h $L/file.h $P/puzzle.h $M/unique.h

all: sudoku

.PHONY: valgrind clean

valgrind: all
	valgrind ./sudoku

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f ../common/*.o
	rm -f ../libcs50/*.o
	rm -f corecd c
	rm -f sudoku

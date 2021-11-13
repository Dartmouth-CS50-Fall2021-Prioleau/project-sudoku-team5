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
C = ./create
L = ./library
P = ./puzzle
S = ./solve


CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C -I$P -I$S -I$L
CC = gcc

MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

OBJS =  $C/create.o  $P/puzzle.o  $S/solve.o $L/memory.o $L/file.o

LIBS = -lm

all: sudoku fuzztesting

sudoku: sudoku.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

fuzztesting: fuzztesting.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


# Dependencies: object files depend on header files
sudoku.o: $C/create.h $P/puzzle.h $S/solve.h $L/memory.h $L/file.h
fuzztesting.o: $C/create.h $P/puzzle.h $S/solve.h $L/memory.h 


.PHONY: valgrind clean

valgrind: all
	valgrind ./sudoku create easy

test:
	bash -v testing.sh

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f ../common/*.o
	rm -f corecd c
	rm -f sudoku

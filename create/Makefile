# Makefile for 'create'

PROG = 
OBJS = create.o ../puzzle/puzzle.o ../solve/solve.o ../library/memory.o
LIBS = -lm
LLIBS = 


# Outside libraries
L = ../library
P = ../puzzle
S = ../solve

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$P -I$S -I$L
CC = gcc
MAKE = make

all: create

create: create.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

#  all dependencies
create.o: $P/puzzle.h $S/solve.h  $L/memory.h

# Valgrind debugging tool
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: unittest unit valgrind clean

unittest: create.c ../unittest.h ../puzzle/puzzle.o ../solve/solve.o  ../library/memory.o
	$(CC) $(CFLAGS) -DUNIT_TEST create.c ../puzzle/puzzle.o ../solve/solve.o ../library/memory.o -o unittest
	./unittest

unit: unittest
	./unittest

# uncommnet here to run valgrind on  querier unittest, qunittest
valgrind: ./unittest
	valgrind ./unittest

#valgrind: $(PROG) 
#	valgrind ./$(PROG) 

clean:
	rm -rf *~ *.o *.dSYM
	rm -f stocks
	rm -f core
	rm -f create
	rm -f unittest


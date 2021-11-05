#Outside libraries
L = ./library
C = ./create
B = ./box
S = ./solve


CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C -I$B -I$S
CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

OBJS = $L/counters.o $C/create.o $B/box.o $L/memory.o $S/solve.o

LIBS =

sudoku: sudoku.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Dependencies: object files depend on header files
sudoku.o: $L/counters.h $C/create.h $B/box.h $L/memory.h $S/solve.h

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f ../common/*.o
	rm -f ../libcs50/*.o
	rm -f corecd c
	rm -f sudoku

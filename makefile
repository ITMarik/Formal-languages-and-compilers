CFLAGS=-std=c99 -Wall -pedantic -g
BIN=project
CC=gcc
RM=rm -

ALL: scanner.o 
	$(CC) $(CFLAGS) -o $(BIN) scanner.o 

clean:
	$(RM) *.o $(BIN)

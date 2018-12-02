CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
OFILES = syntax_analyzer.o strings.o symtable.o stack.o scanner.o
HFILES = syntax_analyzer.h strings.h symtable.h stack.h scanner.h
CC = gcc

syntax_analyzer.o: syntax_analyzer.c $(HFILES)
	$(CC) $(CFLAGS) -c syntax_analyzer.c
	
strings.o: strings.c $(HFILES)
	$(CC) $(CFLAGS) -c strings.c
	
symtable.o: symtable.c $(HFILES)
	$(CC) $(CFLAGS) -c symtable.c
	
stack.o: stack.c $(HFILES)
	$(CC) $(CFLAGS) -c stack.c
	
scanner.o: scanner.c $(HFILES)
	$(CC) $(CFLAGS) -c scanner.c

clean:
	rm $(OFILES)

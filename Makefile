CFLAGS=-std=c99 -Wall -pedantic -g

prekladac: scanner.o symtable.o syntax_analyzer.o main.o exp_analyzer.o strings.o 
	gcc $(CFLAGS) scanner.o symtable.o syntax_analyzer.o main.o exp_analyzer.o strings.o -lm -o prekladac

scanner.o: scanner.c
	gcc $(CFLAGS) -c scanner.c

symtable.o: symtable.c
	gcc $(CFLAGS) -c symtable.c

syntax_analyzer.o: syntax_analyzer.c
	gcc $(CFLAGS) -c syntax_analyzer.c

exp_analyzer.o: exp_analyzer.c
	gcc $(CFLAGS) -c exp_analyzer.c
	
main.o: main.c
	gcc $(CFLAGS) -c main.c
	
strings.o: strings.c
	gcc $(CFLAGS) -c strings.c
	
clean:
	rm -f *.o

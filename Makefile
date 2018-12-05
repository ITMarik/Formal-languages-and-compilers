CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
CC = gcc

interpret: $(FILES)
	$(CC) $(CFLAGS) -o interpret main.c -lm
	



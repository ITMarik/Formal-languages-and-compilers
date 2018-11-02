#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <error_h.h>
#include <scanner.h>

/*******************************	
	File: scanner.c
	Serves for lexical analysis
	Authors : blablabla
	blablabla
*******************************/

//this function saves to field every possible keyword that may occur
int Load_Keyword (token *load, ) {
	char *K_Words[] = {}

int get_token(FILE *fd, token *t) {
	
	int a = 0;

	while (true) {
		a = getc(fd);
		
		switch ();

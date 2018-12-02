#ifndef strings_h
#define strings_h

#include <stdbool.h>
#include <stdio.h>

typedef struct 
{
	char *str;	//place for string
	int length; //real legth of string
	int size; //size of alocated memory
} strings;

void string_clear (strings *s);
int string_init (strings *s);
void string_free (strings *s);
int string_add (strings *s, char c);
int string_compare (strings *retezec_1, strings *retezec_2);
int string_copy (strings *retezec_1, strings *retezec_2);

#endif //_strings_H
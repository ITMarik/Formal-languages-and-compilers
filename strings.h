#ifndef _DYNAMIC_STRING_H
#define _DYNAMIC_STRING_H

#include <stdbool.h>

typedef struct 
{
	char *str;
	unstigned int len;
	unstigned int size;
} dynamic_string;

void string_clear (dynamic_string *s);
bool string_init (dynamic_string *s);
bool string_add (dynamic_string *s, char c);
int string_cmp (dynamic_string *dynamic_string, const char * const_string);
bool string_cp (dynamic_string *ted, dynamic_string *pot);
void string_free (dynamic_string *s);
bool string_add_const (dynamic_string *s, const char *const_string);

#endif //_DYNAMIC_STRING_H
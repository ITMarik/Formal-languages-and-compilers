#ifndef strings_h
#define strings_h

#include <stdbool.h>

typedef struct 
{
	char *str;
	unsigned int length;
	unsigned int size;
} strings;

void string_clear (strings *s);
bool string_init (strings *s);
bool string_add (strings *s, char c);
int string_cmp (strings *strings, const char * const_string);
bool string_cp (strings *ted, strings *pot);
void string_free (strings *s);
bool string_add_const (strings *s, const char *const_string);

#endif //_strings_H
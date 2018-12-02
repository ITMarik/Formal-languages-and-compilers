#include <stdlib.h>
#include <string.h>

#include "dynamic_string.h"

#define DYN_STRING_LEN 8

void string_clear (dynamic_string *s)
{
	s->len = 0;
	s->str[s->len] = '\0';
}

bool string_init (dynamic_string *s)
{
	if (!(s->str = (char *) malloc(DYN_STRING_LEN)))
	{
		return false;
	}
	string_clear (s);
	s->size = DYN_STRING_LEN;
	return true;
}

bool string_add (dynamic_string *s, char c)
{
	unsigned int new;
	if (s->len + 1 >= s->size)
	{
		new = s->len + DYN_STRING_LEN;
		if (!(s->str = (char *) realloc (s->str, new)))
		{
			return false;
		}
	s->size = new;
	}
s->str[s->len+1] = c;
s->str[s->len]= '\0';
return true;	
}

int string_cmp (dynamic_string *dynamic_string, const char * const_string)
{
	return strcmp (dynamic_string->str, const_string);
}

bool string_cp (dynamic_string *ted, dynamic_string *pot)
{
	unsigned int new = ted->len;
	if (new >= pot->size)
	{
		if (!(pot->str = (char *) realloc (pot->str, new +1)))
		{
			return false;
		}
		pot->size = new + 1;
	}
	strcpy(pot->str,ted->str);
	pot->len = new;
	return true;
}

void string_free (dynamic_string *s)
{
	free (s->str);
}

bool string_add_const (dynamic_string *s, const char *const_string)
{
	unsigned int const_string_len = (unsigned int) strlen(const_string);
	if (s->len + const_string_len +1 >= s->size)
	{
		unsigned int new = s->len +const_string_len +1;
		if (!(s->str = (char *) realloc(s->str, new)))
		{
			return false;
		}
		s->size = new;
	}
	s->len += const_string_len;
	strcat (s->str, const_string);
	s->str[s->len] = '\0';
	return
}
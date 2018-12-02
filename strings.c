#include <stdlib.h>
#include <string.h>

#include "strings.h"

#define STRING_LENGTH 8 //pocatecni alokace - na 8 bitu
#define S_OK 0
#define S_WRONG 1


void string_clear (strings *s)
{
    s->length = 0;
    s->str[0] = '\0';
}

bool string_init (strings *s)
{
	if (!(s->str = (char *) malloc(STRING_LENGTH)))
	{
		return S_WRONG;
	}
	string_clear (s);
	s->size = STRING_LENGTH;
	return S_OK;
}

int string_add (strings *s, char c)
{
	unsigned int new;
	if (s->length + 1 >= s->size)
	{
		new = s->length + STRING_LENGTH;
		if (!(s->str = (char *) realloc (s->str, new)))
		{
			return S_WRONG;
		}
	s->size = new;
	}
	s->str[s->length] = c;
	S->length++;
	s->str[s->length]= '\0';
	return S_OK;	
}

int string_cmp (strings *strings, const char * const_string)
{
	return strcmp (strings->str, const_string);
}

bool string_cp (strings *ted, strings *pot)
{
	unsigned int new = ted->length;
	if (new >= pot->size)
	{
		if (!(pot->str = (char *) realloc (pot->str, new +1)))
		{
			return false;
		}
		pot->size = new + 1;
	}
	strcpy(pot->str,ted->str);
	pot->length = new;
	return true;
}

void string_free (strings *s)
{
	free (s->str);
}

bool string_add_const (strings *s, const char *const_string)
{
	unsigned int const_STRING_LENGTH = (unsigned int) strlength(const_string);
	if (s->length + const_STRING_LENGTH +1 >= s->size)
	{
		unsigned int new = s->length +const_STRING_LENGTH +1;
		if (!(s->str = (char *) realloc(s->str, new)))
		{
			return false;
		}
		s->size = new;
	}
	s->length += const_STRING_LENGTH;
	strcat (s->str, const_string);
	s->str[s->length] = '\0';
	return
}

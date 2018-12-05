/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        strings.c - rozšíření práce s řetězci		        *
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Členové týmu :  Martin Janda                                         *
 *              :  Marek Šťastný                                        *
 *              :  Martina Tučková                                      *
 *              :  Martina Jendrálová                                   *
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/	

#include <stdlib.h>
#include <string.h>

#include "strings.h"

#define str_length 8 //pocatecni alokace - na 8 bitu
#define S_OK 0
#define S_WRONG 1


void string_clear (strings *s) {
    s->length = 0;
    s->str[0] = '\0';
}

int string_init (strings *s) {
	if (!(s->str = (char *) malloc(str_length)))
	{
		return S_WRONG;
	}
	string_clear (s);
	s->size = str_length;
	return S_OK;
}

void string_free (strings *s) {
	free (s->str);
}

int string_add (strings *s, char c) {

	int helpling;
	if (s->length + 1 >= s->size)
	{
		helpling = s->length + str_length;
		if (!(s->str = (char*)realloc(s->str, helpling)))
		{
			return S_WRONG;
		}
		s->size = helpling;
	}
	s->str[s->length] = c;
	S->length++;
	s->str[s->length]= '\0';
	return S_OK;	
}

int string_compare (strings *retezec_1, strings *retezec_2) {

	return strcmp (retezec1->str, retezec2);
}

int string_copy (strings *retezec_1, strings *retezec_2) { //zkopiruju retezec 1 do retezce 2
	
	int helpling = retezec_1->length;
	if (helpling >= retezec_2->size)
	{
		if (!(retezec_2->str = (char *) realloc (retezec_2->str, helpling +1)))
		{
			return S_WRONG;
		}
		retezec_2->size = helpling + 1;
	}
	strcpy(retezec_2->str,retezec_1->str);
	retezec_2->length = helpling;
	return S_OK;
}


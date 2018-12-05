/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        err.c - funkce pro vypis erroru           		*
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Autoři :  	   Martin Janda (xjanda27)                              *                                 
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/

#include <stdio.h>
#include "err.h"

void vypis_hodnotu(int navratova_hodnota) {

	switch(navratova_hodnota) {
		case 0: fprintf(stderr,"Překlad proběhl bez chyb.\n"); break;
		case 1: fprintf(stderr,"Chyba v programu v rámci lexikální analýzy.\n"); break;
		case 2: fprintf(stderr,"Chyba v programu v rámci syntaktické analýzy.\n"); break;
		case 3: fprintf(stderr,"Sémantická chyba v programu.\n"); break;
		case 4: fprintf(stderr,"Chyba v aritmetických, řetězcových a relačních výrazech.\n"); break;
		case 5: fprintf(stderr,"Špatný počet parametrů volání funkce.\n"); break;
		case 6: fprintf(stderr,"Proběhla jiná, sémantická chyba vedlejšího typu.\n"); break;
		case 9: fprintf(stderr,"Proběhla běhová chyba dělení nulou.\n"); break;
		case 99: fprintf(stderr,"Proběhla Interní chyba přeladače neovlivněná vstupním programem.\n"); break;
	}
}

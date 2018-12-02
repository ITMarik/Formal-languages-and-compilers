#include <stdio.h>


void vypis_chybu(int error) {

	switch(error) {
		case 0: fprintf(stderr,"Vše proběhlo v pořádku\n"); break;
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
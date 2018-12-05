#include <stdio.h>

//#include "scanner.h"
//#include "syntax_analyzer.h"
//#include "err.h"
//#include "generator.h"
//#include "stack.h"
//#include "strings.h"
//#include "symtable.h"

#include "structs.h"
#include "syntax_analyzer.c"
//#include "scanner.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *fp;

int main()
{

int result;





token_t * P_token;
P_token = malloc(sizeof(token_t));
string_init(P_token);
P_token->type = T_FIRST;
printf("main\n");
result = prog(P_token);


if( result == 0 )
{
	printf("parser je vysostne happy\n");
}
else
{
	printf("parser nema radost\n");
}














	
	return result;
}

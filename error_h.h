#include <stdio.h>
#include <stdlib.h>

#ifndef error_h
#define error_h

#define SUCCES 0        //everything was OK
#define LEX_ERROR 1		//there is an error in lexical analysis
#define SYNT_ERROR 2	//there is an error in syntactically analysis
#define SEMANTIC_ERROR 3    //there is an error with undefined function or undefined variable
#define RUNTIME_ERROR 4	    //there is an error in arithmetical, string or relation expresions
#define PARAM_ERROR 5	    //wrong number of parameters
#define OTHER_ERROR 6 	    //other semantic mistake
#define ZERO_DIVISION_ERROR 9	//error in division with 0
#define PARSER_ERROR 99		//error in parser unaffected by input program

#endif

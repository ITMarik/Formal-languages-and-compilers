//Hlavickovy subor pre scanner.c

#ifndef scanner_h
#define scanner_h
#include "syntax_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//18.41
typedef enum { // -13
    START,          // 0, počiatok
    ERROR,
    ID,             // identifikator
    CL,             // čiselný literál
    LBRACKET,       //  (
    RBRACKET,       //  )
    PLUS,           //  +
    MINUS,          //  -
    COMMA,          //  ,
    DOT,            //  .
    LESS,           //  <
    GREATER,        //  >
    TIMES,          //  *
    EQUALS,         //  ==
    DIV,            //  /
    ASSIGNMENT,      //  =
    HASH,           //  #
    BLOCK,          // =begin
    NECO,           //  \
    XXX,              //  "
    EO_L,
    EXCL,           //  !
    QUERY,          //  ?
    ONE,            // rezervné
    Q1,
    Q2,
    Q3,
    Q4,
    Q5,
    RL,
    DOUBLE,
    EXP,
    DL,
    DL2,
    ID2,
    GE,
    LE,
    EXE,
    E_OF,
    EE,             //  = =
    GREATER2,       //  >
    LESS2,          //  <
    DL3,
    DEF,            // KLUCOVE SLOVA :
    DO,
    ELSE,
    END,
    IF,
    NIL,
    THEN,
    WHILE
} automat_type;
//vsechny stavy automatu, snad :D

char *keywords[] = {"def", "do", "else", "end", "if", "nil", "then", "while" };

typedef struct
{
    char *string_value;
   // automat_type type;
    TOKEN_TYPE type;
    int size_alloc;
    int integer; // pre dlzku
   // double decimal;
    float f_value;
}token_t;

int string_init(token_t *xx);
void string_free(token_t *xx);
void string_clean(token_t *xx);
int string_add (token_t *xx, char c);
//int BinaryToDecimal(long long n);
//long long convertOctalToDecimal(int octalNumber);
//int hexadecimalToDecimal(char hexVal[]);
int get_token(token_t* loaded_token);

#endif

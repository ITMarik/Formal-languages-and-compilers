//Hlavickovy subor pre scanner.c

#ifndef scanner_h
#define scanner_h

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//2.14
typedef enum {
    START,          // 0, počiatok
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
    EQUALS,         //  =
    DIV,            //  /
    SEMICOLON,      //  ;
    HASH,           //  #
    BLOCK,          // =begin
    NECO,           //  \
    X,              //  "
    EOL,
    EXCL,           //  !
    QUERY,          //  ?
    ONE,            // rezervné
    ERROR,
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
    automat_type type;
    int size_alloc;
    int integer; // pre dlzku
    double decimal;
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

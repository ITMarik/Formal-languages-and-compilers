#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"

#define string_length 10
#define OK 0

/*************************************************************************************************
************************************_POMOCNE_FUNKCIE_*********************************************
**************************************************************************************************/

int string_init(token_t *xx) {
    if ((xx->string_value = (char *) malloc(string_length)) == NULL)
        return ERROR;
    xx->string_value[0] = '\0';
    xx->integer = 0;
    xx->size_alloc = string_length;
    return OK;
}

void string_free(token_t *xx) {
    free(xx->string_value);
    xx->string_value = NULL;
}

void string_clean(token_t *xx) {
    xx->string_value[0] = '\0';
    xx->integer = 0;
}

int string_add (token_t *xx, char c) {
    if (xx->integer + 1 >= xx->size_alloc) {
        if ((xx->string_value = (char *) realloc(xx->string_value, xx->integer + string_length * sizeof(char))) == NULL)
            return ERROR;
        xx->size_alloc = xx->integer + string_length;
    }
    xx->string_value[xx->integer] = c;
    xx->integer++;
    xx->string_value[xx->integer] = '\0';
    return OK;
}

/// plus dalsie potencionalne pomocné funkcie

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int getToken(token_t *token) {
// hlavni funkce lexikalniho analyzatoru
  //  printf("pred automat type \n");
    automat_type state = START;
    int i = 0; //načitanie tokenu
    string_clean(token);
  //  printf("po clean \n");

    while (1) { //jednicka pro nekonecnou smycku zatim
      //  printf("while \n");

        i = getchar();
     //   printf("TITO\n");
        switch (state) {

            case START:
                if (i == EOL)
                    return EOL;
                if (isspace(i)) {
                    state = START;
             //   } else if (i == '/') { //  delenie
             //       state = ONE;
                } else if (isalpha(i) || i == '_') { // IDentifikator
                    string_add(token, i);
                    state = ID;
                } else if (i == '0') {
                    i = getchar();
                    if (!isdigit(i)) {
                        string_add(token, '0');
                        state = CL;
                    }
                    ungetc(i, stdin);
                } else if (isdigit(i)) {
                    string_add(token, i);
                    state = CL;
                } else if (i == '(') {
                    state = LBRACKET;
                } else if (i == ')') {
                    string_add(token, i);
                    return RBRACKET;
                } else if (i == '+') {
                    string_add(token, i);
                    return PLUS;
                } else if (i == '-') {
                    string_add(token, i);
                    return MINUS;
                } else if (i == ',') {
                    string_add(token, i);
                    return COMMA;
                } else if (i == '.') {
                    string_add(token, i);
                    return DOT;
                } else if (i == '<') {
                    string_add(token, i);
                    state = LESS;
                } else if (i == '>') {
                    string_add(token, i);
                    state = GREATER;
                } else if (i == '*') {
                    string_add(token, i);
                    return TIMES;
                } else if (i == '/') {
                    string_add(token, i);
                    return DIV;
                } else if (i == '=') { // =
                    string_add(token, i);
                    state = EQUALS;
                } else if (i == ';') {
                    string_add(token, i);
                    return SEMICOLON;
                } else if (i == '#') {
                    string_add(token, i);
                    state =  HASH;
               // } else if (i == "=begin") { // mam jakysi neblahy pocit jestli tohle vubec pujde? jestli to neprijima jen po jednotlivych znacich?
               //     state = BLOCK;
                } else if (i == 92) {
                    string_add(token, i);
                    return NECO;    // " \"
                } else if (i == '"') {
                    state = QUOTE;
                } else if (i == 10) {
                    string_add(token, i);//nebo mozna tam dat '/n' ?
                    return EOL;
                } else if (i == '!') {
                    string_add(token, i);
                    state = EXCL;
                } else if (i == '?') {
                    string_add(token, i);
                    return QUERY;
                } else
                    state = ERROR;
                break;

            case HASH: { // tu je riadkovy komentar
                i = getchar();
                if(i != '\n'){
                    state = HASH;
                }
                state = START;
                break;
            }

            case CL :
                i = getchar();
                if (i == '.') {
                    state = DOUBLE;
                } else if (i == 'e' || i == 'E') {
                    state = EXP;
                } else {
                    ungetc(i, stdin);
                }
                break;

            case ID:
                i = getchar();
                if (i == '!' || i == '?')
                    state = START;
                else
                    i = getchar();
                break;

            case DOUBLE: {
                i = getchar();
                if (isdigit(i)) {
                    state = DL; //desetinny literal
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case EXP:
                i = getchar();
                if (isdigit(i) || i == '+' || i == '-') {
                    state = DL2;
                    string_add(token, i);
                } else
                    return ERROR;
                break;

            case DL2:
                i = getchar();
                if (isdigit(i)) {
                    state = DL2;
                    string_add(token, i);
                } else
                    return ERROR;
                break;

            case QUOTE: { // riešenie  pre - " -
                i = getchar();
                if (i > 31 && i <
                              128) { //opisuju tu N.Z. z automatu.. cele N.Z. je {32-127}-{34,92}, uz si nepamatuju co presne to znamena, tak jsem to dala jen takto prozatim, tak klidne to zmen jak je potreba
                    state = QUOTE;
                    string_add(token, i);
                } else if (i == 92) {
                    state = Q1;
                    string_add(token, i);
                } else if (i == '"') {
                    state = RL;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }
            case Q1: {
                i = getchar();
                if (i == 92 || i == 34 || i == 's' || i == 't' || i == 'h') {
                    state = Q2;
                    string_add(token, i);
                } else if (i == 'x') {
                    state = Q3;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q2: {
                i = getchar ();
                if (i == 92) {
                    state = Q1;
                    string_add(token, i);
                } else if (i == '"') {
                    state = RL; //retezcovy literal
                    string_add(token, i);
                } else if (i > 31 && i < 128) { // stejne jako predtim neejsem si jista s N.Z. ktere tu je
                    state = QUOTE; //retezcovy literal
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q3: {
                i = getchar();
                if (isdigit(i) || (i > 64 && i < 71)) { // ASCII pro A..F
                    state = Q4;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q4: {
                i = getchar();
                if (isdigit(i)) { // ASCII pro A..F
                    state = Q5;
                    string_add(token, i);
                } else if (isdigit(i) || (i > 64 && i < 71)) { // opet A..F v ASCII
                    state = Q5;
                    string_add(token, i);
                } else if (i == '"') {
                    state = RL;
                    string_add(token, i);
                } else if (i == 92) {
                    state = Q1;
                    string_add(token, i);
                } else if (i > 31 && i < 128) { // opet N.Z.
                    state = QUOTE;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q5: {
                i = getchar();
                if (i == '"') {
                    state = RL;
                    string_add(token, i);
                } else if (i == 92 || (i > 31 && i < 128)) {
                    state = Q1;
                    string_add(token, i);
                } else if (i > 31 && i < 128) { // opet N.Z.
                    state = QUOTE;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case GREATER: {
                i = getchar();
                if (i == '=') {
                    state = GREATER;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }
            case LESS: {
                i = getchar();
                if (i == '=') {
                    state = LESS;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }
            case EXCL: {
                i = getchar();
                if (i == '=') {
                    state = EXE;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case EQUALS: {
                i = getchar();
                if (i == '=') {
                    state = EE;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }
            default:
                break;
        }
    }
}


int main (int argc, char ** argv){
    FILE *source;
    int need;

    source = fopen(argv[1], "r");
    token_t next_token;
    string_init(&next_token);

    if(argc == 1 ){
        return ERROR;
    }
    if (source == NULL){
        printf("Subor sa nepodarilo otvorit\n");
        return ERROR;
    }

    do {
       // printf("Ano \n");
        need = getToken(&next_token);
        //printf("po need \n");
        printf(" ..........Tu je niečo napisane  \n");
    } while (need != 39); //EOF

    string_free(&next_token);
    fclose(source);

    return 0;
}
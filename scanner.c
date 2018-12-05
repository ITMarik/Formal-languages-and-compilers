/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        scanner.c                                            *
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Autori :        Martina Tučková       (xtucko00)                     *
 *                 Martina Jendrálová    (xjendr03)                     *
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "scanner.h"
#include "err.h"

#define string_length 10
#define OK 0
//23.47

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

int compare( token_t *xx, char* yy) {
    return strcmp(xx->string_value, yy);
}

int is_it_end(int i){
    if (i == ' ' || i == '\n' || i == EOF){
        return true;
    }else
        return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int BinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, zbytek;
    while (n!=0)
    {
        zbytek = n%10;
        n /= 10;
        decimalNumber += zbytek*pow(2,i);
        ++i;
    }
    return decimalNumber;
}


long long convertOctalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0)
    {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}


// Function to convert hexadecimal to decimal
int hexadecimalToDecimal(char hexVal[])
{
    int len = strlen(hexVal);

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i=len-1; i>=0; i--)
    {
        if (hexVal[i]>='0' && hexVal[i]<='9')
        {
            dec_val += (hexVal[i] - 48)*base;

            base = base * 16;
        }

        else if (hexVal[i]>='A' && hexVal[i]<='F')
        {
            dec_val += (hexVal[i] - 55)*base;

            base = base*16;
        }
    }

    return dec_val;
}

/// plus dalsie potencionalne pomocné funkcie

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int getToken(token_t *token) {
// hlavni funkce lexikalniho analyzatoru

    //printf("Mimo WHILE !!!!! \n ");

    automat_type state = START;
    int i = 0; //načítanie tokenu

    // matematicke premenne
    int helper = 1; //pomocna pri '=begin' r. 336  / '=end
    int helper_exp = 0;
    int a = 1;
    int f = 0;
    float c = 1;
    float d = (float) -1.0;
    float b = 0.0;
    float help_exp = 0.0;
    float help = 0.0;
    string_clean(token);

    while (1) { //jednicka pro nekonecnou smycku zatim

        i = getchar();
        //printf("Sme vo while ♥ \n\n");

        switch (state) {

            case START:
                if (i == '\n') {
                    token->type = T_EOL;
                    return OK;
                }
                if (i == EOF ){
                    token->type = T_EOF;
                    return OK;
                }
                if (isspace(i)) {
                    state = START;
                } else if ((i > 96 && i <123 )|| i == '_') { // IDentifikator ...je to male pismeno ? alebo '_'
                    string_add(token, i);
                    state = ID;
                } else if (i == '0') {
                    string_add(token, i);
                    //token->f_value = 0.0;
                    i = getchar(); //divne
                    if (!isdigit(i)) { // je to cislo ? 0..9
                        state = CL;
                    }
                    ungetc(i, stdin);
                } else if (isdigit(i)) { //    0..9
                    string_add(token, i);
                    help = i - 48;
                    state = CL;
                } else if (i == '(') {
                    string_add(token, i);
                    token->type = T_L_BRACKET;
                    return OK;
                } else if (i == ')') {
                    string_add(token, ')');
                    token->type = T_R_BRACKET;
                    return OK;
                } else if (i == '+') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF){
                        token->type = T_PLUS;
                        return OK;
                    }else{
                        return ERROR;
                    }
                } else if (i == '-') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF){
                        token->type = T_MINUS;
                        return OK;
                    }else{
                        return ERROR;
                    }
                } else if (i == ',') {
                    string_add(token, ',');
                    token->type = T_COMMA;
                    return OK;
                } else if (i == '<') {
                    string_add(token, i);
                    state = LESS;
                } else if (i == '>') {
                    string_add(token, i);
                    state = GREATER;
                } else if (i == '*') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF){
                    token->type = T_MULTIPLICATION;
                    return OK;
                    }else{
                        return ERROR;
                    }
                } else if (i == '/') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF){
                        token->type = T_DIVISION;
                        return OK;
                    }else{
                        return ERROR;
                    }
                } else if (i == '=') {
                    state = EQUALS;
                } else if (i == '#') {
                   // string_add(token, i);
                    state =  HASH;
                } else if (i == '"') {
                    string_add(token, i);
                    state = 18;
                } else if (i == '\n') {
                    string_add(token, i);
                    token->type = T_EOL;
                    return OK;
                } else if (i == '!') {
                    string_add(token, i);
                    state = EXCL;
                } else {
                    //printf("VSTUP TYMTO ZACIATOCNYM ZNAKOM NIE JE POVOLENY !!!!\n");
                    return ERROR;
                }
                break;

            case HASH: { // tu je riadkovy komentar
               string_add(token, i);
                if(i != '\n' || i != EOF){
                    state = HASH;
                    string_add(token, i);

                }else {
                    return OK;
                    //printf("Tu je komentár, ktorý nemame vracat ..zasa !\n");
                }
                break;
            } //corect

            case EQUALS: { //pokracovanie '=' ...mame uložene v tokene
                if (i == ' ' || i == '\n' || i == EOF){
                    string_add(token, '=');
                    token->type = T_ASSIGNMENT;
                    return OK;
                }else if (i == '=') {
                    string_add(token, i);
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF) {
                        token->type = T_EQUAL;
                        return OK;
                    }else{
                        return ERROR;
                    }
                }else if(i == 'b'){
                    //string_add(token, i);
                    helper = getchar();
                    //string_add(token, helper);
                    if (helper == 'e'){
                        helper = getchar();
                       // string_add(token, helper);
                        if (helper == 'g'){
                            helper = getchar();
                            //string_add(token, helper);
                            if (helper == 'i'){
                                helper = getchar();
                                //string_add(token, helper);
                                if (helper == 'n'){
                                    if (token->type == T_FIRST ){
                                        state = BLOCK;
                                        //printf("IDEME DO BLOCKU !!! \n");
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    //printf("SPATNEEE!!!!");
                    return ERROR;
                }
                break;
            }

            case BLOCK:{ // blokový komentár
                //string_add(token, i);
                if(i == '\n') {
                    helper = getchar();
                    //string_add(token, helper);
                    if (helper == '=') {
                        helper = getchar();
                        //string_add(token, helper);
                        if (helper == 'e') {
                            helper = getchar();
                           // string_add(token, helper);
                            if (helper == 'n') {
                                helper = getchar();
                                string_add(token, helper);
                                if (helper == ('d')) {
                                    //printf("Tu je komentár, ktorý nemame vracať\n");
                                    helper = getchar();
                                    if (helper != EOF){
                                        //("IDEME DO HASHU !!!! ♥\n");
                                        state = HASH;
                                    }
                                }
                            }
                        }
                    }
                }else {
                    //printf("        TU SME SPATNEEE ..TU NEMAME BYT BLOCK !!!x\n");
                    state = BLOCK;
                    break;
                }
                break;
            }//corect

            case CL :
                if (i == '.') {
                    string_add(token, i);
                    state = DOUBLE;
                } else if (i == 'e' || i == 'E') {
                    string_add(token, i);
                    state = EXP;
                }else if (i > 47 && i < 58){
                    string_add(token, i);
                    i = i - 48;
                    help = i +(help * 10);
                    helper++;
                    state = CL;
                } else if(!(i > 47 && i < 58)) {
                    token->type = T_INT;
                    token->f_value = help;
                    return OK;
                } else {
                    ungetc(i, stdin);
                }
                break;

            case ID: //az na EOF is correct
                if (!(i == ' ' || i == '\n' || i == EOF || i == '!' || i == '?')) { //ak to NIE je medzera, \n alebo koniec suboru a zaroven to NIE je ani ?,!
                    if (i == 95 || i == 44 || (i > 47 && i < 58) || isalpha(i)) { // ak je to _ alebo 0 .. 9 uloži a ide dalej
                        //if (i != 44) {
                            string_add(token, i);

                            if (compare(token, "do") == 0) {// klucove slova
                                token->type = T_DO;
                                return OK;
                            } else if (compare(token, "if") == 0) {
                                token->type = T_IF;
                                return OK;
                            } else if (compare(token, "def") == 0) {
                                token->type = T_DEF;
                                return OK;
                            } else if (compare(token, "end") == 0) {
                                token->type = T_END;
                                return OK;
                            } else if (compare(token, "nil") == 0) {
                                token->type = T_NIL;
                                return OK;
                            } else if (compare(token, "else") == 0) {
                                token->type = T_ELSE;
                                return OK;
                            } else if (compare(token, "then") == 0) {
                                token->type = T_THEN;
                                return OK;
                            } else if (compare(token, "while") == 0) {
                                token->type = T_WHILE;
                                return OK;
                            }
                       // }else{
                         //   state = COMMA;
                           // break;
                        //}
                    } else {//
                        return ERROR;

                        //printf("PADLI SME NA ERRORE NA ID !!!!..........♠ \n");
                        return ERROR;
                    }
                    state = ID;
                } else {
                    if(i == '!' || i == '?')
                        string_add(token,i);
                    //printf("DOSTALI SME SA NA KONIEC ID !!!!..........♥\n");
                    token->type = T_ID;
                    return OK;
                }
                break;


            case DOUBLE: {
                if (!(i == 'e' || i == 'E')) {
                    if (!(i == ' ' || i == '\n' || i == EOF)) {
                        if (isdigit(i)) {//desetinny literal
                            string_add(token, i); //strtof()
                            i = i - 48;
                            b = b + (i / (pow(10, a)));
                            a++;
                            //printf("\n");
                            state = DOUBLE;
                        } else
                            return ERROR;
                    } else {
                        b = help + b;
                        token->type = T_FLOAT;
                        token->f_value = b;
                        return OK;
                    }
                }else{
                    string_add(token,i);
                    b = help + b;
                    state = DL;
                }
                break;
            }
            case DL:{
                if (!(i == ' ' || i == '\n' || i == EOF)) {
                    if( i == '+' || i == '-'){
                        string_add(token, i);
                        f = i;
                        i = getchar();
                        if(helper_exp == 0){
                            if(f == 45){
                                c = c * d;
                            }
                        } else {
                            return ERROR;
                        }
                    }
                    if (isdigit(i)) {//desetinny literal 0.58e14 napr.
                        string_add(token, i);
                        i = i - 48;
                        help_exp = i + (help_exp * (pow(10, helper_exp)));
                        helper_exp++;
                        state = DL;
                    } else{
                        return ERROR;
                    }
                } else {
                    if (helper_exp == 0) {
                        return ERROR;
                    }else{
                        help_exp = help_exp * c ;
                        b = pow(b, help_exp);
                        //printf("\n");
                        token->type = T_FLOAT;
                        token->f_value = b;
                        return OK;
                        break;
                    }
                }break;
            }

            case EXP:
                if (!(i == ' ' || i == '\n' || i == EOF)) {
                    if(i == '+' || i == '-'){
                        string_add(token,i);
                        f = i;
                        i = getchar();
                        if(helper_exp == 0){
                            if ( f == 45){
                                c = c * d;
                            }
                        } else{
                            return ERROR;
                        }
                    }
                    if (isdigit(i)) {
                        //setinny literal 0.58e14 napr.
                            string_add(token, i);
                            i = i - 48;
                            help_exp = i + (help_exp * (pow(10, helper_exp)));
                            helper_exp++;
                            state = EXP;
                        } else
                            return ERROR;
                    } else {
                        if (helper_exp == 0){
                            return ERROR;
                        }else{
                            help_exp = help_exp * c;
                            state = DL2;
                            break;
                        }
                } break;

            case DL2:
                help_exp = pow(help, help_exp);
                    token->type = T_FLOAT;
                    token->f_value = help_exp;
                    return OK;
                    break;

            //*tento stav je ako jediny pomenovany cislom, pretoze nam na nom z nejakeho
            // neznameho dovodu nechcel fungovat povodny nazov QUOTE, ktory bol typu automat_type, dakuujem za pochopenie

            case 18: { // riešenie  pre - " -
                if (i > 31 && i < 128 && i != 34 && i != 92) { //opisuju tu N.Z. z automatu.. cele N.Z. je {32-127}-{34,92}, uz si nepamatuju co presne to znamena, tak jsem to dala jen takto prozatim, tak klidne to zmen jak je potreba
                    state = 18;
                    string_add(token, i);
                } else if (i == 92) { //corect
                    state = Q1;
                    string_add(token, i);
                } else if (i == '"') {
                    string_add(token, i);
                    token->type = T_STRING;
                    return OK;
                } else
                    return ERROR;
                break;
            }
            case Q1: { //   - \ -
                if (i == 92 || i == 34 || i == 's' || i == 't' || i == 'n') {
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
                if (i == 92) {
                    state = Q1; // tymto som si nie uplne ista
                    string_add(token, i);
                } else if (i == '"') {
                    string_add(token, i);
                    token->type = T_STRING;
                    return OK; //retezcovy literal
                } else if (i > 31 && i < 128 && i != 34 && i != 92) { // stejne jako predtim neejsem si jista s N.Z. ktere tu je
                    state = 18; //retezcovy literal
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q3: {
                if (isdigit(i) || (i > 64 && i < 71)) { // ASCII pro A..F
                    state = Q4;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q4: {
                if (isdigit(i) || (i > 64 && i < 71)) { // opet A..F v ASCII
                    state = Q5;
                    string_add(token, i);
                } else if (i == '"') {
                    string_add(token, i);
                    token->type = T_STRING;
                    return OK;
                    string_add(token, i);
                } else if (i == 92) {
                    state = Q1;
                    string_add(token, i);
                } else if (i > 31 && i < 128 && i != 34 && i != 92) { // opet N.Z.
                    state = 18;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case Q5: {
                if (i == '"') {
                    string_add(token, i);
                    token->type = T_STRING;
                    return OK;
                } else if (i == 92 ) {
                    state = Q1;
                    string_add(token, i);
                } else if (i > 31 && i < 128 && i != 34 && i != 92) { // opet N.Z.
                    state = 18;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case GREATER: { // pokracovanie >
                if (i == ' ' || i == '\n' || i == EOF){
                    token->type = T_GREATER;
                    return OK;
                }else if (i == '=') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF) {
                        string_add(token, i);
                        token->type = T_GREATER_EQUAL;
                        return OK;
                    } else{
                        return ERROR;
                    }
                }else
                    return ERROR;
                break;
            }

            case LESS: { // pokracovanie <
                if (i == ' ' || i == '\n' || i == EOF){
                    token->type = T_LESS;
                    return OK;
                }else if (i == '=') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF) {
                        string_add(token, i);
                        token->type = T_LESS_EQUAL;
                        return OK;
                    } else{
                        return ERROR;
                    }
                } else
                    return ERROR;
                break;
            }

            case EXCL: {
                if (i == '=') {
                    string_add(token, i);
                    i = getchar();
                    if (i == ' ' || i == '\n' || i == EOF) {
                        token->type = T_NOT_EQUAL;
                        return OK;
                    } else {
                        return ERROR;
                    }
                }
                return ERROR;
                break;
            }

            default:
                break;
        }
    }
    //printf("............JE TO KONIEC SUBORU ! .............\n\n");
    token->type = T_EOF;
    return OK;
 } // end of get_token ...38

/*
// vnútro mainu treba zakomentovať !!!!!!!!!!!!!!!!!!!!
int main (int argc, char ** argv){
    int need;

    token_t next_token;
    string_init(&next_token);
    next_token.type = T_FIRST;
    do {
        //printf("\n \n");
        //printf("PREBERAME DALSI TOKEN !!!!! \n");
        need = getToken(&next_token);
        if (need == 1){
            printf("\n\n");
            printf("                                 ABSOLUTE ERROR !!!!!! ####### !!!!!!!!!\n\n");
            break;
        }


        printf("number: %d  \t----length: %d\t----buffer: %s \t----type: %d\t----f_value: %f   \n", need, next_token.size_alloc, next_token.string_value, next_token.type,next_token.f_value);
    } while (next_token.type != T_EOF ); //EOF

    string_free(&next_token);

    return 0;
}
*/

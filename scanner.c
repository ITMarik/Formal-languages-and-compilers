#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "scanner.h"
#include "err.h"

#define string_length 10
#define OK 0
//0.18

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
/*
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
*/

/// plus dalsie potencionalne pomocné funkcie

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int getToken(token_t *token) {
// hlavni funkce lexikalniho analyzatoru

    //printf("Mimo WHILE !!!!! \n ");

    automat_type state = START;
    int i = 0; //načítanie tokenu
    int helper = 1; //pomocna pri '=begin' r. 336  / '=end
    int helper_exp = 0;
    float help_exp = 0.0;
    float help = 0.0;

    string_clean(token);

    while ((i = getchar()) != EOF) { //jednicka pro nekonecnou smycku zatim

        //printf("Sme vo while ♥ \n\n");

        switch (state) {

            case START:
                if (i == '\n')
                    return EO_L;
                    token->type = EO_L ;
                if (isspace(i)) {
                    state = START;
                } else if (isalpha(i) || i == '_') { // IDentifikator
                    string_add(token, i);
                    state = ID;
                } else if (i == '0') {
                    string_add(token, i);
                    token->f_value = 0.0;
                    i = getchar(); //divne
                    if (!isdigit(i)) {
                        state = CL;
                    }
                    ungetc(i, stdin);
                } else if (isdigit(i)) {
                    string_add(token, i);
                    help = i - 48;
                    state = CL;
                } else if (i == '(') {
                    string_add(token, i);
                    token->type = T_L_BRACKET;
                    return LBRACKET;
                } else if (i == ')') {
                    string_add(token, i);
                    token->type = T_R_BRACKET;
                    return RBRACKET;
                } else if (i == '+') {
                    string_add(token, i);
                    token->type = T_PLUS;
                    token->type = T_PLUS;
                    return PLUS;
                } else if (i == '-') {
                    string_add(token, i);
                    token->type = T_MINUS;
                    return MINUS;
                } else if (i == ',') {
                    string_add(token, i);
                    token->type = T_COMMA;
                    return COMMA;
                } else if (i == '<') {
                    string_add(token, i);
                    state = LESS;
                } else if (i == '>') {
                    string_add(token, i);
                    state = GREATER;
                } else if (i == '*') {
                    string_add(token, i);
                    token->type = T_MULTIPLICATION;
                    return TIMES;
                } else if (i == '/') {
                    string_add(token, i);
                    token->type = T_DIVISION;
                    return DIV;
                } else if (i == '=') {
                    //string_add(token, i);
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
                    return EO_L;
                } else if (i == '!') {
                    string_add(token, i);
                    state = EXCL;
                } else
                    state = ERROR;
                break;

            case HASH: { // tu je riadkovy komentar
               // string_add(token, i);
                if(i != '\n'){
                    state = HASH;
                }else {
                    state = START;
                    printf("Tu je komentár, ktorý nemame vracat ..zasa !\n");
                }
                break;
            } //corect

            case EQUALS: { //pokracovanie '=' ...mame uložene v tokene
                if (i == '=') {
                    string_add(token, i);
                    string_add(token, i);
                    token->type = T_EQUAL;
                    return EE;
                } else
                if(i == 'b'){
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
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    printf("SPATNEEE!!!!");
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
                                //string_add(token, helper);
                                if (helper == ('d')) {
                                    printf("Tu je komentár, ktorý nemame vracať\n");
                                    state = HASH;
                                }
                            }
                        }
                    }
                }else
                state = BLOCK;
                break;
            }//corect

            case CL :
                if (i == '.') {
                    string_add(token, i);
                    state = DOUBLE;
                } else if (i == 'e' || i == 'E') {
                    state = EXP;
                }else if (i > 47 && i < 58){
                    string_add(token, i);
                    state = CL;
                } else if(!(i > 47 && i < 58)){
                    //printf("Takto ? too byt nemaaa !!! \n");
                    return ONE;
                } else {
                    ungetc(i, stdin);
                }
                break;

            case ID:
                if(i == 95)
                    state = ID;
                if (i > 47 && i < 58){
                    //string_add(token, i);
                    state = ID;
                }
                //printf("Sme v ID !!... %d \n",i);
                string_add(token, i);
                if (is_it_end(i)) { //??????????
                    printf("Bolo to IDentifikator\n");
                    token->type = T_ID;
                    return ID;
                    break;
                }
                else
                    if (compare(token, "do") == 0) return DO;
                    else if (compare(token, "if") == 0) return IF;
                    i = getchar();
                    if (i == '!' || i == '?'){
                        string_add(token, i);
                        i = getchar();
                        if ((is_it_end(i))){
                            printf("OKKK !!!\n");
                            return ID;
                        }else{
                            printf("SPAAAATNE !!!!\n");
                            return ERROR;
                        }
                    }
                    string_add(token, i);
                    if (compare(token, "def") == 0){
                        token->type = T_DEF;
                        return DEF;
                    } 		// klucove slova
                    else if (compare(token, "end") == 0){
                        token->type = T_END;
                        return END;
                    }
                    else if (compare(token, "nil") == 0){
                        token->type = T_NIL;
                        return NIL;
                    }
                    i = getchar();
                    if (i == '!' || i == '?'|| i == ' ') return ID;
                    string_add(token, i);
                    if (compare(token, "else") == 0){
                        token->type = T_ELSE;
                        return ELSE;
                    }
                    else if (compare(token, "then") == 0){
                        token->type = T_THEN;
                        return THEN;
                    }
                    i = getchar();
                    if (i == '!' || i == '?'|| i == ' ') return ID;
                    string_add(token, i);
                    if (compare(token, "while") == 0){
                        token->type = T_WHILE;
                        return WHILE;
                    }
                break;

            case DOUBLE: {
                if (!(i == 'e' || i == 'E')) {
                    if (!(is_it_end(i))) {
                        if (isdigit(i)) {//desetinny literal
                            printf("ASCII hodnota i : %d.........\n", i);
                            string_add(token, i); //strtof()
                            i = i - 48;
                            printf("Skutocna hodnota i : %d.............\n", i);
                            help = help + (i / (pow(10, helper)));
                            helper++;
                            printf(".....HELP DOUBLE JE :%f.........\n", help);
                            printf("\n");
                            state = DOUBLE;
                        } else
                            return ERROR;
                    } else {
                        token->type = T_FLOAT;
                        token->f_value = help;
                        printf("KONIEC AUTOMAT DOUBLE !! \n");
                        printf("\n");
                        return DOUBLE;
                    }
                }else{
                    string_add(token,i);
                    state = DL;
                }
                break;
            }
            case DL:{
                if (!(is_it_end(i))) {
                    if (isdigit(i)) {//desetinny literal 0.58e14 napr.
                        printf("ASCII hodnota exponentu i : %d.........\n", i);
                        string_add(token, i);
                        i = i - 48;
                        help_exp = i + (help_exp * (pow(10, helper_exp)));
                        helper_exp++;
                        printf("Skutocna hodnota exponentu i : %d.............\n", i);
                        printf("EXPONENT : %f.........\n", help_exp);
                        printf("\n");
                        state = DL;
                    } else
                        return ERROR;
                } else {
                    state = DL3;
                    break;
                }
            }
// z nejakeho dôvodu to vyskakuje sem von skor ako  ma !!!!!!!!!!!!!!
            case DL3:{
                printf(" %f  na   %f ....je : \n",help, help_exp);
                help = pow(help, help_exp);
                printf("Vysledok : %f...........\n", help);
                printf("\n");
                token->type = T_FLOAT;
                token->f_value = help;
                printf("EXPONENT HOTOVO!! \n");
                break;
            }


            case EXP:
                if (isdigit(i) || i == '+' || i == '-') {
                    state = DL2;
                    string_add(token, i);
                } else
                    return ERROR;
                break;

            case DL2:
                if (isdigit(i)) {
                    state = DL2;
                    string_add(token, i);
                } else
                    return ERROR;
                break;

            //*tento stav je ako jediny pomenovany cislom, pretoze nam na nom z nejakeho
            // neznameho dovodu nechcel fungovat povodny nazov QUOTE, ktory bol typu automat_type, dakuujem za pochopenie
            case 18: { // riešenie  pre - " -
                if (i > 31 && i < 128) { //opisuju tu N.Z. z automatu.. cele N.Z. je {32-127}-{34,92}, uz si nepamatuju co presne to znamena, tak jsem to dala jen takto prozatim, tak klidne to zmen jak je potreba
                    state = 18;
                    string_add(token, i);
                } else if (i == 92) {
                    state = Q1;
                    string_add(token, i);
                } else if (i == '"') {
                    string_add(token, i);
                    token->type = T_STRING;
                    return RL;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }
            case Q1: { //   - \ -
                if (i == 92 || i == 34 || i == 's' || i == 't' || i == 'h') {//preco h ?
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
                    return RL; //retezcovy literal
                    string_add(token, i);
                } else if (i > 31 && i < 128) { // stejne jako predtim neejsem si jista s N.Z. ktere tu je
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
                if (isdigit(i)) { // ASCII pro A..F
                    state = Q5;
                    string_add(token, i);
                } else if (isdigit(i) || (i > 64 && i < 71)) { // opet A..F v ASCII
                    state = Q5;
                    string_add(token, i);
                } else if (i == '"') {
                    string_add(token, i);
                    token->type = T_STRING;
                    return RL;
                    string_add(token, i);
                } else if (i == 92) {
                    state = Q1;
                    string_add(token, i);
                } else if (i > 31 && i < 128) { // opet N.Z.
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
                    return RL;
                    string_add(token, i);
                } else if (i == 92 || (i > 31 && i < 128)) {
                    state = Q1;
                    string_add(token, i);
                } else if (i > 31 && i < 128) { // opet N.Z.
                    state = 18;
                    string_add(token, i);
                } else
                    return ERROR;
                break;
            }

            case GREATER: {
                if((i = getchar()) == 32) { // OPRAVIť
                    token->type = T_GREATER;
                    return GREATER2;
                }else if (i == '=') {
                    string_add(token, i);
                    token->type = T_GREATER_EQUAL;
                    return GREATER;
                }else
                    return ERROR;
                break;
            }
            case LESS: {
                if ((i = getchar()) == 32){
                    token->type = T_LESS;
                    return LESS2;
                }else if (i == '=') {
                    string_add(token, i);
                    token->type = T_LESS_EQUAL;
                    return LESS;
                } else
                    return ERROR;
                break;
            }
            case EXCL: {
              //  if ()
                if (i == '=') {
                    string_add(token, i);
                    token->type = T_NOT_EQUAL;
                    return EXE;
                } else
                    return ERROR;
                break;
            }

            default:
                break;
        }
    }
    token->type = T_EOF;
    return E_OF;
 } // end of get_token ...38


// vnútro mainu treba zakomentovať !!!!!!!!!!!!!!!!!!!!
int main (int argc, char ** argv){
    int need;

    token_t next_token;
    string_init(&next_token);
    next_token.type = T_FIRST;
    do {
        printf("\n \n");
        printf("PREBERAME DALSI TOKEN !!!!! \n");
        need = getToken(&next_token);
        if (need == 22)
            break;
        printf("number: %d  \t----length: %d\t----buffer: %s \t----type: %d\t----f_value: %f   \n", need, next_token.size_alloc, next_token.string_value, next_token.type,next_token.f_value);
    } while (need != E_OF); //EOF

    string_free(&next_token);

    return 0;
}

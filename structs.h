#ifndef structs_h
#define structs_h


#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define SUCCES 0     //everything was OK
#define LEX_ERROR 1		//there is an error in lexical analysis
#define SYNT_ERROR 2	//there is an error in syntactically analysis
#define SEMANTIC_ERROR 3  //there is an error with undefined function or undefined variable
#define RUNTIME_ERROR 4	  //there is an error in arithmetical, string or relation expresions
#define PARAM_ERROR 5	   //wrong number of parameters
#define OTHER_ERROR 6 	 //other semantic mistake
#define ZERO_DIVISION_ERROR 9	//error in division with 0
#define PARSER_ERROR 99	//error in parser unaffected by input program



typedef enum token_type
{
	T_DEF,
	T_ID,
	T_IF,
	T_WHILE,
	T_DO,
	T_ELSE,	// 5
	T_END,
	T_THEN,
	T_ASSIGNMENT,
	T_EOL,
	T_EOF,
	T_COMMA, // 11
	T_STRING,
	T_INT,
	T_FLOAT,
	T_L_BRACKET,
	T_R_BRACKET, // 16
	T_PLUS,
	T_MINUS,
	T_MULTIPLICATION,
	T_DIVISION,
	T_EQUAL, //21
	T_NOT_EQUAL,
	T_LESS,
	T_GREATER,
	T_LESS_EQUAL,
	T_GREATER_EQUAL,
	T_NIL,
	T_FIRST
} TOKEN_TYPE;



typedef struct konecny_token
{
    char *string_value;
   // automat_type type;
    TOKEN_TYPE type;
    int size_alloc;
    int integer; // pre dlzku
   // double decimal;
    float f_value;
}token_t;

typedef struct token
{
	TOKEN_TYPE type;
	void *p_token_attributes;
} t_token ;	
	 
	 
bool id_is_operand();
bool is_exp(token_t *P_token );
int term(token_t *P_token);
int term_part(token_t * P_token);
int term_list(token_t *P_token);
int assignment(token_t *P_token);
int assigned(token_t *P_token);
int part(token_t *P_token);
int param_list(token_t * P_token);
int param_group(token_t * P_token);
int f_call(token_t * P_token);
int stat(token_t * P_token);
int stat_list(token_t * P_token);
int prog(token_t *P_token);





///////////////////////////////////////////////////////////////////////
#define table_size 14


typedef enum ITEM_TYPE
{
	X_PLUS,			// 0
	X_MINUS,		// 1
	X_MULTIPLICATION,	// 2
	X_DIVISION,		// 3
	X_LESS,			// 4
	X_GREATER,		// 5
	X_LESS_EQUAL,		// 6	
	X_GREATER_EQUAL,	// 7
	X_EQUAL,		// 8 
	X_NOT_EQUAL,		// 9
	X_L_BRACKET,		// 10
	X_R_BRACKET,		// 11
	X_I,			// 12
	X_DOLLAR,		// 13

	X_NONTERMINAL,		// 14
	X_STOP,			// 15
	
	X_HANDLE_PLUS,
	X_HANDLE_MINUS,
	X_HANDLE_MULTIPLICATION,
	X_HANDLE_DIVISION,
	X_HANDLE_LESS,
	X_HANDLE_GREATER,
	X_HANDLE_LESS_EQUAL,
	X_HANDLE_GREATER_EQUAL,
	X_HANDLE_EQUAL,
	X_HANDLE_NOT_EQUAL,
	X_HANDLE_L_BRACKET,
	NOTHING,
	X_HANDLE_I,
	X_HANDLE_DOLLAR
	


} ITEM_TYPE;




char precedence_table [table_size][table_size] = {

//			  +    -    *    /    <    >    <=   >=   ==   !=   (    )    i    $
	/* +  */	{'>', '>', '<', '<', '>', '>', '<', '<', '<', '<', '<', '>', '<', '>'},
	/* -  */	{'>', '>', '<', '<', '>', '>', '<', '<', '<', '<', '<', '>', '<', '>'},
	/* *  */	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>'},
	/* /  */	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>'},
	/* <  */	{'<', '<', '<', '<', 'x', 'x', 'x', 'x', 'x', 'x', '<', '>', '<', '>'},
	/* >  */	{'<', '<', '<', '<', 'x', 'x', 'x', 'x', 'x', 'x', '<', '>', '<', '>'},
	/* <= */	{'<', '<', '<', '<', 'x', 'x', 'x', 'x', 'x', 'x', '<', '>', '<', '>'},
	/* >= */	{'<', '<', '<', '<', 'x', 'x', 'x', 'x', 'x', 'x', '<', '>', '<', '>'},
	/* == */	{'<', '<', '<', '<', 'x', 'x', 'x', 'x', 'x', 'x', '<', '>', '<', '>'},
	/* != */	{'<', '<', '<', '<', 'x', 'x', 'x', 'x', 'x', 'x', '<', '>', '<', '>'},
	/* (  */	{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', 'x'},
	/* )  */	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'x', '>', 'x', '>'},
	/* i  */	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'x', '>', 'x', '>'},
	/* $  */	{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', 'x', '<', 'x'},
};


	
typedef struct precedence_item
{
	ITEM_TYPE type;
	struct precedence_item * next;
} t_precedence_item;



ITEM_TYPE handle[5]; //5 maximalni delka handle
//v poli bude handle reverzne



bool start_handle(ITEM_TYPE type);
void from_stack_to_handle(ITEM_TYPE * pole, t_precedence_item *stack);
bool rule(ITEM_TYPE handle[5], int *rule_id );
void remove_handle(t_precedence_item ** top);
ITEM_TYPE type_of_token(token_t *P_token);
void push(ITEM_TYPE type, t_precedence_item **top);
t_precedence_item *top(t_precedence_item * stack );
void top_to_handle(t_precedence_item * stack );
void print_stack(t_precedence_item* pointer);





///////////////////////////////////////////////////////////////////////////////
//13.05
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
    NECO,           //  
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


int string_init(token_t *xx);
void string_free(token_t *xx);
void string_clean(token_t *xx);
int string_add (token_t *xx, char c);
//int BinaryToDecimal(long long n);
//long long convertOctalToDecimal(int octalNumber);
//int hexadecimalToDecimal(char hexVal[]);
int get_token(token_t* loaded_token);

#endif


#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>






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
	T_EOL,
	T_EOF,
	T_COMMA, // 10
	T_STRING,
	T_INT,
	T_FLOAT,
	T_L_BRACKET,
	T_R_BRACKET, // 15
	T_PLUS,
	T_MINUS,
	T_MULTIPLICATION,
	T_DIVISION,
	T_EQUAL, //20
	T_NOT_EQUAL,
	T_LESS,
	T_GREATER,
	T_LESS_EQUAL,
	T_GREATER_EQUAL,
	T_NIL
} TOKEN_TYPE;


typedef struct token
{
	TOKEN_TYPE type;
	void *p_token_attributes;
} t_token;	
	 
	 

void next_token(int *ToKeN_OrDeR, t_token *P_token);

bool assigned(int * ToKeN_OrDeR, t_token *P_token);
bool f_call(int *ToKeN_OrDeR, t_token * P_token);
bool stat_list(int *ToKeN_OrDeR, t_token * P_token);








void next_token(int *ToKeN_OrDeR, t_token *P_token)
{
	(*ToKeN_OrDeR) ++;
							
	switch(*ToKeN_OrDeR)
	{
		case 1:
		P_token->type = T_DEF;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 2:
		P_token->type = T_ID;
		P_token->p_token_attributes = NULL;
		break; 
	
		case 3:
		P_token->type = T_L_BRACKET;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 4:
		P_token->type = T_ID;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 5:
		P_token->type = T_COMMA;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 6:
		P_token->type = T_ID;
		P_token->p_token_attributes = NULL;
		break;
		
		case 7:
		P_token->type = T_R_BRACKET;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 8:
		P_token->type = T_EOL;
		P_token->p_token_attributes = NULL;
		break;
		
		case 9:
		P_token->type = T_ID;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 10:
		P_token->type = T_EQUAL;
		P_token->p_token_attributes = NULL;
		break; 
	
		case 11:
		P_token->type = T_INT;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 12:
		P_token->type = T_EOL;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 13:
		P_token->type = T_END;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 14:
		P_token->type = T_EOL;
		P_token->p_token_attributes = NULL;
		break;
		
		case 15:
		P_token->type = T_EOF;
		P_token->p_token_attributes = NULL;
		break; 
		
		case 16:
		P_token->type = T_EOF;
		P_token->p_token_attributes = NULL;
		break;

		default:
		P_token->type = T_COMMA; 
	} 
	printf("predavam token :%d\n", P_token->type);
}

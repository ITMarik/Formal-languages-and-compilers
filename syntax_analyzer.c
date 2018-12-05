/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        syntax_analyzer.c 				        *
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Autoři       :  Martin Janda                                         *
 *              :  Marek Šťastný                                        *
 *              :  Martina Tučková                                      *
 *              :  Martina Jendrálová                                   *
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/

//#include "syntax_analyzer.h"
//#include "exp_analyzer.h"

#include "structs.h"
#include "scanner.c"
#include "exp_analyzer.c"



bool id_is_operand()	// demoverze
{
	return false;
}





bool is_exp( token_t *P_token  )
{
	if( P_token->type == T_L_BRACKET || P_token->type == T_STRING || P_token->type == T_INT || P_token->type == T_FLOAT )
	{
//		printf("funkce is_exp: true1\n");
		return true;
	}
	
	else if( P_token->type == T_ID )
	{
		if( id_is_operand(P_token) ) // funkce zjisti na zaklade nalezeni polozky v symtable
		{
///			printf("funkce is_exp: true\n");
			return true;
		}
	}
//	printf("funkce is_exp: false\n");
	return false;
}





int term(token_t *P_token)
{
//	printf("funkce term\n");
	if(P_token->type == T_ID)
	//simulace pravidla 25
	{
		
//		printf("funkce term pravidlo 25: true\n");
		return getToken( P_token) ;
	}
	else if(P_token->type == T_INT)
	//simulace pravidla 26
	{
		
//		printf("funkce term pravidlo 26: true\n");
		return getToken( P_token);
	}
	else if(P_token->type == T_FLOAT)
	//simulace pravidla 27
	{
//		printf("funkce term pravidlo 27: true\n");
		return getToken( P_token);
	}
	else if(P_token->type == T_STRING)
	//simulace pravidla 28
	{
//		printf("funkce term pravidlo 29: true\n");
		return getToken( P_token);
	}
	else if(P_token->type == T_NIL)
	//simulace pravidla 29
	{

//		printf("funkce term pravidlo 29: true\n");
		return  getToken( P_token);
	}
	return SYNT_ERROR;
}





int term_part(token_t * P_token)
{
	int result;
//	printf("funkce term_part\n");
	if(P_token->type == T_COMMA)
	//simulace pravidla 23
	{
		if(getToken( P_token) == LEX_ERROR)
		{		
			return LEX_ERROR;
		}
		result = term( P_token);	
		if( result == SUCCES )
		{
			return term_part( P_token);
		}
		else
			return result;
	}
	else if( P_token->type == T_EOL || P_token->type == T_R_BRACKET)
	//simulace pravidla 24
	{
//		printf("funkce term_part pravidlo 24: true\n");
		return SUCCES;
	}
	return SYNT_ERROR;
}





int term_list(token_t *P_token)
{
	int result;
//	printf("funkce term_list\n");
	if( P_token->type == T_ID || P_token->type == T_INT || P_token->type == T_FLOAT || P_token->type == T_STRING || P_token->type == T_NIL )
	//simulace pravidla 22
	{
		result = term( P_token);
		if( result == SUCCES )
		{
			return term_part( P_token);
		}
		else
		{
			return result;
		}	
	}
	else if( P_token->type == T_EOL || P_token->type == T_R_BRACKET )
	{
	//simulace pravidla 21
//		printf("term_list pravidlo 21: true\n");
		return SUCCES;
	}
	return SYNT_ERROR;
}





int assignment(token_t *P_token)
{
//	printf("funkce assignment\n");
	if(P_token->type == T_EOL)
	//simulace pravidla 14
	{
//		printf("assignment pravidlo 14: true\n");
		return SUCCES;
	}
	else if(P_token->type == T_ASSIGNMENT)
	//simulace pravidla 15
	{
		if( getToken( P_token) == LEX_ERROR)
			return LEX_ERROR;
		{
		return assigned( P_token);
		}
	}
	return SYNT_ERROR;
}
		




int assigned(token_t *P_token)
{
int result;
//	printf("funkce assigned\n");
	if( is_exp(P_token) )
	//simulace pravidla 16
	{
//		printf("assigned prvni vetev\n");
		result = expression( P_token);
		return result;	
	}
	else if(P_token->type == T_ID)
	//simulace pravidla 17
	{
		result = f_call( P_token);
		return result;
	}
	return SYNT_ERROR;
}





int part(token_t *P_token)
{
//	printf("funkce part\n");
	if(P_token->type == T_COMMA)
	//simulace pravidla 8
	{
		if (getToken( P_token) == LEX_ERROR)
		{
			return LEX_ERROR;
		}
		if(P_token->type == T_ID)
		{
			if (getToken( P_token) == LEX_ERROR)
			{
				return LEX_ERROR;
			}			
			return part( P_token);
		}
	}
	else if(P_token->type == T_R_BRACKET)
	//simulace pravidla 9
	{
		return SUCCES;
	}
//	printf("funkce part: false\n");
	return SYNT_ERROR;
}






int param_list(token_t * P_token)
{
//	printf("funkce param_list\n");
	if(P_token->type == T_ID)
	//simulace pravidla 7
	{
		if(getToken( P_token)== LEX_ERROR)
		{	
			return LEX_ERROR;
		}
		return part( P_token);
	}
	else if(P_token->type == T_R_BRACKET)
	//simulace pravidla 6
	{
//		printf("funkce param_list: true\n");
		return SUCCES;
	}
//	printf("funkce param_list: false\n");
	return SYNT_ERROR;
}





int param_group(token_t * P_token)
{
//	printf("funkce param_group\n");
	if(P_token->type == T_ID || P_token->type ==  T_EOL || P_token->type ==  T_INT || P_token->type ==  T_FLOAT 
	|| P_token->type ==  T_STRING || P_token->type ==  T_NIL )
	//simulace pravidla 19
	{
		return term_list( P_token);
	}
	else if(P_token->type == T_L_BRACKET)
	//simulace pravidla 20
	{
		if( getToken( P_token) == LEX_ERROR)
		{
			return LEX_ERROR;
		}
		if( term_list( P_token)==SUCCES )
		{
			if(P_token->type == T_R_BRACKET)
			{
				if(getToken( P_token)== LEX_ERROR)
				{	
					return LEX_ERROR;
				}
//				printf("funkce param_group: true\n");
				return SUCCES;
			}
		}
	}	
//	printf("funkce param_group: false\n");
	return SYNT_ERROR;
}





int f_call(token_t * P_token)
{
//	printf("funkce f_call\n");
	if(P_token->type == T_ID)
	//simulace pravidla 18
	{
		if(getToken( P_token) == LEX_ERROR)
		{
			return LEX_ERROR;
		}
		return param_group( P_token);
	}
//	printf("funkce f_call: false\n");
	return SYNT_ERROR;
}


	


int stat(token_t * P_token)
{
//	printf("funkce stat\n");
	if(P_token->type == T_EOL)
	// simulace pravidla 4
	{
		return SUCCES;
	}
	else if(P_token->type == T_DEF)
	//simulace pravidla 5
	{
		if(getToken( P_token)==LEX_ERROR)
			return LEX_ERROR;
		if(P_token->type == T_ID)
		{
			if(getToken( P_token)==LEX_ERROR)
				return LEX_ERROR;
			if(P_token->type == T_L_BRACKET)
			{
				if(getToken( P_token)==LEX_ERROR)
					return LEX_ERROR;
				if( param_list( P_token)==SUCCES)
				{
					if(P_token->type == T_R_BRACKET)
					{
						if(getToken( P_token)==LEX_ERROR)
							return LEX_ERROR;
						if(P_token->type == T_EOL)
						{
							if(getToken( P_token)==LEX_ERROR)
							return LEX_ERROR;
							if( stat_list( P_token)==SUCCES )
							{
								if(P_token->type == T_END)
								{
									if(getToken( P_token)==LEX_ERROR)
										return LEX_ERROR;
									return SUCCES;
								}
							}
						}
					}
				}
			}
		}
	}
	else if( is_exp(P_token) )
	//simulace pravidla 10
	{
		return expression( P_token);	
	}
	else if(P_token->type == T_IF)
	//simulace pravidla 11
	{
		if(getToken( P_token)==LEX_ERROR)
			return LEX_ERROR;
		if( is_exp(P_token) )
		{
			if( expression( P_token) )
			{
				if(P_token->type == T_THEN)
				{
					if(getToken( P_token)==LEX_ERROR)
						return LEX_ERROR;
					if(P_token->type == T_EOL)
					{
						if(getToken( P_token)==LEX_ERROR)
							return LEX_ERROR;
						if( stat_list( P_token)==SUCCES )
						{
							if(P_token->type == T_ELSE)
							{
								if(getToken( P_token)==LEX_ERROR)
									return LEX_ERROR;
								if(P_token->type == T_EOL)
								{
									if(getToken( P_token)==LEX_ERROR)
										return LEX_ERROR;
									if( stat_list( P_token)==SUCCES )
									{
										if(P_token->type == T_END)
										{
											if(getToken( P_token)==LEX_ERROR)
												return LEX_ERROR;
											return SUCCES;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if(P_token->type == T_WHILE)
	//simulace pravidla 12
	{
//printf("stat while\n");
		if(getToken( P_token)==LEX_ERROR)
		{	
//	printf("token ee\n");
			return LEX_ERROR;
		}		
		if( is_exp(P_token) )
		{
//printf("hh\n");
			if( expression( P_token) )
			{
//printf("jnsjdnjsni\n");
				if(P_token->type == T_DO)
				{
					if(getToken( P_token)==LEX_ERROR)
						return LEX_ERROR;
					if(P_token->type == T_EOL)
					{
						if(getToken( P_token)==LEX_ERROR)
							return LEX_ERROR;
						if( stat_list( P_token) == SUCCES )
						{
							if(P_token->type == T_END)
							{
								if(getToken( P_token)==LEX_ERROR)
									return LEX_ERROR;
								return SUCCES;
							}
						}
					}
				}
			}
		}
	}
	else if(P_token->type == T_ID)
	//simulace pravidla 13
	{
//		printf("funkce stat pravidlo 13\n");
		if(getToken( P_token)==LEX_ERROR)
			return LEX_ERROR;
		if( assignment( P_token) ==SUCCES)
		{
//			printf("stat pravidlo 13: true\n");	
			return SUCCES;
		}
		
	}

//	printf("funkce stat: false %dkoko\n",SYNT_ERROR);
	return SYNT_ERROR;
}





int stat_list(token_t * P_token)
{
//	printf("stat_list\n");
	if( P_token->type == T_DEF || P_token->type == T_IF || P_token->type == T_WHILE || P_token->type == T_EOL ||
	is_exp(P_token) || P_token->type == T_ID)
	//simulace pravidla 2
	{
		if( stat( P_token) == SUCCES  )
		{
			if(P_token->type == T_EOL)
			{
				if(getToken( P_token)==LEX_ERROR)
					return LEX_ERROR;
				return stat_list( P_token);
			}
		}
	}
	else if( P_token->type == T_ELSE || P_token->type == T_END || P_token->type == T_EOF )
	//simulace pravidla 3
	  {
//		printf("list vraci true\n");
		return SUCCES;
	  }
	  
//	printf("funkce stat_list: false\n");
	  return SYNT_ERROR;
}





int prog(token_t *P_token)
//funkce si zavola prvni token sama
{
	//printf("funkce prog\n");
	if(getToken( P_token)==LEX_ERROR)
		return LEX_ERROR;	//vyjimka tato funkce simuluje startujici neterminal, zavola siprvni token sama
//printf("dostal jsem token\n");
	int result = SYNT_ERROR;	

	if( P_token->type == T_DEF || P_token->type == T_IF || P_token->type == T_WHILE || P_token->type == T_EOL ||
	P_token->type == T_EOF || is_exp(P_token) || P_token->type == T_ID )				//is expression by mel byt vzdy volan pred porovnavanim na ID
	//simulace pravidla 1
	{
		if( stat_list( P_token) == SUCCES )
		{
			result = (P_token->type == T_EOF);
		//	getToken(P_token, ToKeN_OrDeRi);  //vyjimka za EOF uz neni dalsi token  
		}
	}
	return result;
}



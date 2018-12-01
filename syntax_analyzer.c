#include "syntax_analyzer.h"


bool expression(int *ToKeN_OrDeR, t_token *P_token)
//funkce zpracovavajici vyrazy
//P_token je ukazatel na prvni token vyrazu
//po dokonceni bude v P_token prvni token ktery nasleduje za exp
{
	if(P_token->type == T_INT)	//
	{
		next_token(ToKeN_OrDeR, P_token);
		printf("funkce expression: true\n");
		return true;		//
	}
	else				//demoverze pozdeji smazat
	{	
		printf("funkce expression: false\n");
		return false;		//
	}
}




bool id_is_operand(t_token *token)	// demoverze
{
	return false;
}





bool is_exp( t_token *P_token  )
{
	if( P_token->type == T_L_BRACKET || P_token->type == T_STRING || P_token->type == T_INT || P_token->type == T_FLOAT )
	{
		printf("funkce is_exp: true1\n");
		return true;
	}
	
	else if( P_token->type == T_ID )
	{
		if( id_is_operand(P_token) ) // funkce zjisti na zaklade nalezeni polozky v symtable
		{
			printf("funkce is_exp: true\n");
			return true;
		}
	}
	printf("funkce is_exp: false\n");
	return false;
}





bool term(int *ToKeN_OrDeR, t_token *P_token)
{
	printf("funkce term\n");
	if(P_token->type == T_ID)
	//simulace pravidla 25
	{
		next_token(ToKeN_OrDeR, P_token);
		printf("funkce term pravidlo 25: true\n");
		return true;
	}
	else if(P_token->type == T_INT)
	//simulace pravidla 26
	{
		next_token(ToKeN_OrDeR, P_token);
		printf("funkce term pravidlo 26: true\n");
		return true;
	}
	else if(P_token->type == T_FLOAT)
	//simulace pravidla 27
	{
		next_token(ToKeN_OrDeR, P_token);
		printf("funkce term pravidlo 27: true\n");
		return true;
	}
	else if(P_token->type == T_STRING)
	//simulace pravidla 28
	{
		next_token(ToKeN_OrDeR, P_token);
		printf("funkce term pravidlo 29: true\n");
		return true;
	}
	else if(P_token->type == T_NIL)
	//simulace pravidla 29
	{
		next_token(ToKeN_OrDeR, P_token);
		printf("funkce term pravidlo 29: true\n");
		return true;
	}
	return false;
}





bool term_part(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("funkce term_part\n");
	if(P_token->type == T_COMMA)
	//simulace pravidla 23
	{
		next_token(ToKeN_OrDeR, P_token);
		if( term(ToKeN_OrDeR, P_token) )
		{
			return term_part(ToKeN_OrDeR, P_token);
		}
	}
	else if( P_token->type == T_EOL || P_token->type == T_R_BRACKET)
	//simulace pravidla 24
	{
		printf("funkce term_part pravidlo 24: true\n");
		return true;
	}
	return false;
}





bool term_list(int *ToKeN_OrDeR, t_token *P_token)
{
	printf("funkce term_list\n");
	if( P_token->type == T_ID || P_token->type == T_INT || P_token->type == T_FLOAT || P_token->type == T_STRING || P_token->type == T_NIL )
	//simulace pravidla 22
	{
		if( term(ToKeN_OrDeR, P_token) )
		{
			return term_part(ToKeN_OrDeR, P_token);
		}
	}
	else if( P_token->type == T_EOL || P_token->type == T_R_BRACKET )
	{
	//simulace pravidla 21
		printf("term_list pravidlo 21: true\n");
		return true;
	}
	return false;
}





bool assignment(int *ToKeN_OrDeR, t_token *P_token)
{
	printf("funkce assignment\n");
	if(P_token->type == T_EOL)
	//simulace pravidla 14
	{
		printf("assignment pravidlo 14: true\n");
		return true;
	}
	else if(P_token->type == T_EQUAL)
	//simulace pravidla 15
	{
		next_token(ToKeN_OrDeR, P_token);
		return assigned(ToKeN_OrDeR, P_token);
	}
	return false;
}
		




bool assigned(int * ToKeN_OrDeR, t_token *P_token)
{
printf("funkce assigned\n");
	if( is_exp(P_token) )
	//simulace pravidla 16
	{
		printf("assigned prvni vetev\n");
		return expression(ToKeN_OrDeR, P_token);
	}
	else if(P_token->type == T_ID)
	//simulace pravidla 17
	{
		return f_call(ToKeN_OrDeR, P_token);
	}
}





bool part(int *ToKeN_OrDeR, t_token *P_token)
{
	printf("funkce part\n");
	if(P_token->type == T_COMMA)
	//simulace pravidla 8
	{
		next_token(ToKeN_OrDeR, P_token);
		if(P_token->type == T_ID)
		{
			next_token(ToKeN_OrDeR, P_token);
			return part(ToKeN_OrDeR, P_token);
		}
	}
	else if(P_token->type == T_R_BRACKET)
	//simulace pravidla 9
	{
		return true;
	}
	printf("funkce part: false\n");
	return false;
}






bool param_list(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("funkce param_list\n");
	if(P_token->type == T_ID)
	//simulace pravidla 7
	{
		next_token(ToKeN_OrDeR, P_token);
		return part(ToKeN_OrDeR, P_token);
	}
	else if(P_token->type == T_R_BRACKET)
	//simulace pravidla 6
	{
		printf("funkce param_list: true\n");
		return true;
	}
	printf("funkce param_list: false\n");
	return false;
}





bool param_group(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("funkce param_group\n");
	if(P_token->type == T_ID || P_token->type ==  T_EOL || P_token->type ==  T_INT || P_token->type ==  T_FLOAT 
	|| P_token->type ==  T_STRING || P_token->type ==  T_NIL )
	//simulace pravidla 19
	{
		return term_list(ToKeN_OrDeR, P_token);
	}
	else if(P_token->type == T_L_BRACKET)
	//simulace pravidla 20
	{
		next_token(ToKeN_OrDeR, P_token);
		if( term_list(ToKeN_OrDeR, P_token) )
		{
			if(P_token->type == T_R_BRACKET)
			{
				next_token(ToKeN_OrDeR, P_token);
				printf("funkce param_group: true\n");
				return true;
			}
		}
	}	
	printf("funkce param_group: false\n");
	return false;
}





bool f_call(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("funkce f_call\n");
	if(P_token->type == T_ID)
	//simulace pravidla 18
	{
		next_token(ToKeN_OrDeR, P_token);
		return param_group(ToKeN_OrDeR, P_token);
	}
	printf("funkce f_call: false\n");
	return false;
}


	


bool stat(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("funkce stat\n");
	if(P_token->type == T_EOL)
	// simulace pravidla 4
	{
		return true;
	}
	else if(P_token->type == T_DEF)
	//simulace pravidla 5
	{
		next_token(ToKeN_OrDeR, P_token);
		if(P_token->type == T_ID)
		{
			next_token(ToKeN_OrDeR, P_token);
			if(P_token->type == T_L_BRACKET)
			{
				next_token(ToKeN_OrDeR, P_token);
				if( param_list(ToKeN_OrDeR, P_token))
				{
					if(P_token->type == T_R_BRACKET)
					{
						next_token(ToKeN_OrDeR, P_token);
						if(P_token->type == T_EOL)
						{
							next_token(ToKeN_OrDeR, P_token);
							if( stat_list(ToKeN_OrDeR, P_token) )
							{
								if(P_token->type == T_END)
								{
									next_token(ToKeN_OrDeR, P_token);
									return true;
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
		return expression(ToKeN_OrDeR, P_token);	
	}
	else if(P_token->type == T_IF)
	//simulace pravidla 11
	{
		next_token(ToKeN_OrDeR, P_token);
		if( is_exp(P_token) )
		{
			if( expression(ToKeN_OrDeR, P_token) );
			{
				if(P_token->type == T_THEN);
				{
					next_token(ToKeN_OrDeR, P_token);
					if(P_token->type == T_EOL)
					{
						next_token(ToKeN_OrDeR, P_token);
						if( stat_list(ToKeN_OrDeR, P_token) )
						{
							if(P_token->type == T_ELSE)
							{
								next_token(ToKeN_OrDeR, P_token);
								if(P_token->type == T_EOL)
								{
									next_token(ToKeN_OrDeR, P_token);
									if( stat_list(ToKeN_OrDeR, P_token) )
									{
										if(P_token->type == T_END)
										{
											next_token(ToKeN_OrDeR, P_token);
											return true;
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
		next_token(ToKeN_OrDeR, P_token);
		if( is_exp(P_token) )
		{
			if( expression(ToKeN_OrDeR, P_token) );
			{
				if(P_token->type == T_DO)
				{
					next_token(ToKeN_OrDeR, P_token);
					if(P_token->type == T_EOL)
					{
						next_token(ToKeN_OrDeR, P_token);
						if( stat_list(ToKeN_OrDeR, P_token) )
						{
							if(P_token->type == T_END)
							{
								next_token(ToKeN_OrDeR, P_token);
								return true;
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
		printf("funkce stat pravidlo 13\n");
		next_token(ToKeN_OrDeR, P_token);
		if( assignment(ToKeN_OrDeR, P_token) )
		{
			printf("stat pravidlo 13: true\n");	
			return true;
		}
		
	}

	printf("funkce stat: false\n");
	return false;
}





bool stat_list(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("stat_list\n");
	if( P_token->type == T_DEF || P_token->type == T_IF || P_token->type == T_WHILE || P_token->type == T_EOL ||
	is_exp(P_token) || P_token->type == T_ID)
	//simulace pravidla 2
	{
		if( stat(ToKeN_OrDeR, P_token) )
		{
			if(P_token->type == T_EOL)
			{
				next_token(ToKeN_OrDeR, P_token);
				return stat_list(ToKeN_OrDeR, P_token);
			}
		}
	}
	else if( P_token->type == T_ELSE || P_token->type == T_END || P_token->type == T_EOF )
	//simulace pravidla 3
	  {
		printf("list vraci true\n");
		return true;
	  }
	  
	printf("funkce stat_list: false\n");
	  return false;
}





bool prog(int *ToKeN_OrDeR, t_token *P_token)
//funkce si zavola prvni token sama
{
	printf("funkce prog\n");
	next_token(ToKeN_OrDeR, P_token);	//vyjimka tato funkce simuluje startujici neterminal, zavola siprvni token sama
	bool result = false;	

	if( P_token->type == T_DEF || P_token->type == T_IF || P_token->type == T_WHILE || P_token->type == T_EOL ||
	P_token->type == T_EOF || is_exp(P_token) || P_token->type == T_ID )				//is expression by mel byt vzdy volan pred porovnavanim na ID
	//simulace pravidla 1
	{
		if( stat_list(ToKeN_OrDeR, P_token) )
		{
			result = (P_token->type == T_EOF);
		//	next_token(P_token, ToKeN_OrDeRi);  //vyjimka za EOF uz neni dalsi token  
		}
	}

	return result;
}





int main()
{
	bool result;
	int ToKeN_OrDeR = 0;
	t_token *P_token;
	
	result = prog(&ToKeN_OrDeR, P_token);
	if(result)
	{
		printf("syntakticky je vstup spravne\n");
	}
	
	else
	{
		printf("syntakticky je vstup spatne\n");
	}
}

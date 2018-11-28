#include "syntax_analyzer.h"


bool expression(int *ToKeN_OrDeR, t_token *P_token)
//funkce zpracovavajici vyrazy
//P_token je ukazatel na prvni token vyrazu
//po dokonceni bude v P_token prvni token ktery nasleduje za exp
{
	next_token(ToKeN_OrDeR, P_token);
	if(P_token->type == T_ID)	//
		return true;		//
	else				//demoverze pozdeji smazat
		return false;		//
}




bool id_is_operand(t_token *token)	// demoverze
{
	return true;
}





bool is_exp( t_token *token  )
{
	printf("funkce is exp\n");
	if( token->type == T_L_BRACKET || token->type == T_STRING || token->type == T_INT || token->type == T_FLOAT )
	{
		return true;
	}
	
	else if( token->type == T_ID )
	{
		if( id_is_operand(token) ) // funkce zjisti na zaklade nalezeni polozky v symtable
		{
			return true;
		}
	}
	return false;
}





bool assigned(int * ToKeN_OrDeR, t_token *P_token)
{
	if( is_exp(P_token) )
	//simulace pravidla 15
	{
		return expression(ToKeN_OrDeR, P_token);
	}
	else if(P_token->type == T_ID)
	//simulace pravidla 16
	{
		next_token(ToKeN_OrDeR, P_token);
		return f_call(ToKeN_OrDeR, P_token);
	}
}





bool part(int *ToKeN_OrDeR, t_token *P_token)
{
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
	else if(P_token->type == T_R_BRACKET || P_token->type == T_EOL)
	//simulace pravidla 9
	{
		next_token(ToKeN_OrDeR, P_token);
		return true;
	}
	return false;
}






bool param_list(int *ToKeN_OrDeR, t_token * P_token)
{
	if(P_token->type == T_ID)
	//simulace pravidla 7
	{
		next_token(ToKeN_OrDeR, P_token);
		return part(ToKeN_OrDeR, P_token);
	}
	return false;
}





bool param_group(int *ToKeN_OrDeR, t_token * P_token)
{
	if(P_token->type == T_ID || P_token->type ==  T_EOL)
	//simulace pravidla 10
	{
		return param_list(ToKeN_OrDeR, P_token);
	}
	else if(P_token->type == T_L_BRACKET)
	//simulace pravidla 18
	{
		next_token(ToKeN_OrDeR, P_token);
		if( param_list(ToKeN_OrDeR, P_token) )
		{
			if(P_token->type == T_R_BRACKET)
			{
				next_token(ToKeN_OrDeR, P_token);
				return true;
			}
		}
	}
	return false;
}





bool f_call(int *ToKeN_OrDeR, t_token * P_token)
{
	if(P_token->type == T_R_BRACKET || P_token->type == T_EOL)
	//simulace pravidla 6
	{
		return true;
	}
	else if(P_token->type == T_ID)
	//simulace pravidla 17
	{
		next_token(ToKeN_OrDeR, P_token);
		return param_group(ToKeN_OrDeR, P_token);
	}
	return false;
}


	


bool stat(int *ToKeN_OrDeR, t_token * P_token)
{
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
	//simulace pravidla 11
	{
		if( expression(ToKeN_OrDeR, P_token) );
		{
			if(P_token->type == T_EOL)
			{
				return true;
			}
		}
	}
	else if(P_token->type == T_IF)
	//simulace pravidla 12
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
	//simulace pravidla 13
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
	//simulace pravidla 14
	{
		next_token(ToKeN_OrDeR, P_token);
		if(P_token->type == T_EQUAL)
		{
			next_token(ToKeN_OrDeR, P_token);
			if( assigned(ToKeN_OrDeR, P_token) )
			{
				if(P_token->type == T_EOL)
				{
					next_token(ToKeN_OrDeR, P_token);
					return true;
				}
			}
		}
	}

	return false;
}





bool stat_list(int *ToKeN_OrDeR, t_token * P_token)
{
	printf("list\n");
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
	  
	  return false;
}





bool prog(int *ToKeN_OrDeR, t_token *P_token)
//funkce si zavola prvni token sama
{
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

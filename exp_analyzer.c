/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        exp_analyzer.c 				        *
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Autoři       :  Martin Janda                                         *
 *              :  Marek Šťastný                                        *
 *              :  Martina Tučková                                      *
 *              :  Martina Jendrálová                                   *
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/


//#include "exp_analyzer.h"
#include "structs.h"
//#include "scanner.c"






bool rule(ITEM_TYPE handle[5], int *rule_id )
{
	if(handle[0]==X_I && start_handle(handle[1]) && handle[2]==X_STOP)
	{
	//pravidlo 1: E -> i
		*rule_id = 1;
		return true;
	}
	if(handle[0]==X_R_BRACKET && handle[1]==X_NONTERMINAL && handle[2]==X_L_BRACKET && start_handle(handle[3]) && handle[4]==X_STOP)
	{
	//pravidlo 2: E -> (E)
		*rule_id = 2;
		return true;
	}
	if(handle[0]==X_NONTERMINAL && handle[2]==X_NONTERMINAL && start_handle(handle[3]) && handle[4]==X_STOP)
	{
		if(handle[1]== X_PLUS)
		{
			//pravidlo 3: E -> E+E
			*rule_id = 3;
			return true;
		}
		if(handle[1]== X_MINUS)
		{
			//pravidlo 4: E -> E-E
			*rule_id = 4;
			return true;
		}
		if(handle[1]== X_MULTIPLICATION)
		{
			//pravidlo 5: E -> E*E
			*rule_id = 5;
			return true;
		}
		if(handle[1]== X_DIVISION)
		{
			//pravidlo 6: E -> E/E
			*rule_id = 6;
			return true;
		}
		if(handle[1]== X_LESS)
		{
			//pravidlo 7: E -> E<E
			*rule_id = 7;
			return true;
		}
		if(handle[1]== X_GREATER)
		{
			//pravidlo 8: E -> E>E
			*rule_id = 8;
			return true;
		}
		if(handle[1]== X_LESS_EQUAL)
		{
			//pravidlo 9: E -> E<=E
			*rule_id = 9;
			return true;
		}
		if(handle[1]== X_GREATER_EQUAL)
		{
			//pravidlo 10: E -> E>=E
			*rule_id = 10;
			return true;
		}
		if(handle[1]== X_EQUAL)
		{
			//pravidlo 11: E -> E==E
			*rule_id = 11;
			return true;
		}
		if(handle[1]== X_NOT_EQUAL)
		{
			//pravidlo 12: E -> E!=E
			*rule_id = 12;
			return true;
		}
	}
	return false;
}









void remove_handle(t_precedence_item ** top)
{
	t_precedence_item * p_item;
	t_precedence_item * p_help;
	p_item = *top;
	
	while( ! start_handle(p_item->type))
	{
		p_help = p_item;
		p_item = p_item->next;
		free(p_help);
	}
	p_item->type = (p_item->type - 16); // oddelani zacatek handle na normalni terminal
	*top = p_item;
}




bool start_handle(ITEM_TYPE type)
{
 	return (type == X_HANDLE_PLUS || type==X_HANDLE_MINUS || type==X_HANDLE_MULTIPLICATION ||
		type==X_HANDLE_DIVISION || type==X_HANDLE_LESS || type==X_HANDLE_GREATER ||
		type==X_HANDLE_LESS_EQUAL || type==X_HANDLE_GREATER_EQUAL || type==X_HANDLE_EQUAL ||
		type==X_HANDLE_NOT_EQUAL || type==X_HANDLE_L_BRACKET || type==X_HANDLE_I ||
		type==X_HANDLE_DOLLAR);
}




t_precedence_item *top(t_precedence_item * stack )
//vraci prvni neterminal ze stacku
{
	t_precedence_item * p_precedence_item = stack;

	while (p_precedence_item->type == X_NONTERMINAL)
	{
		p_precedence_item = p_precedence_item->next;
	}
	return p_precedence_item;
}



void top_to_handle(t_precedence_item * stack )
//vraci prvni neterminal ze stacku
{
	t_precedence_item * p_precedence_item = stack;

	while (p_precedence_item->type == X_NONTERMINAL)
	{
		p_precedence_item = p_precedence_item->next;
	}
	p_precedence_item-> type = (p_precedence_item->type +16);
}




void print_stack(t_precedence_item* pointer)
{
	while (pointer != NULL)
	{
		pointer = pointer->next;
	}
}




void push(ITEM_TYPE type, t_precedence_item **top)
//funkce prida na vrchol zasobniku novy prvek s typem type
//pokud je pronter na stack NULL prida novy prvek
{
	t_precedence_item * p_precedence_item;
	p_precedence_item = malloc(sizeof(t_precedence_item));
	if(*top == NULL)
	{
		*top = p_precedence_item;
		(*top)-> type = type;
	}
	else
	{
		p_precedence_item->next = *top;
		*top = p_precedence_item;
		(*top)->type = type;
	}
}





void from_stack_to_handle(ITEM_TYPE * pole, t_precedence_item *stack)
//nemeni stack
{
	t_precedence_item *p_item = stack;
	int i = 0;
/*
printf("co je ve stacku\n");
while (p_item != NULL)
{
	printf("%d\n",p_item->type);
	p_item = p_item->next;
}
*/

	while(i<=4)
	{
		*pole = p_item->type;
		if( start_handle(handle[i]) )
		{
			pole++;
			*pole=X_STOP;
			break;
		}
		p_item=p_item->next;
		i++;
		pole++;
	}
}




bool expression(token_t *p_token)
{
	
	int rule_id;
	t_precedence_item *p_stack_item;
	t_precedence_item * p_stack = NULL;
	ITEM_TYPE stack_top_type, input_type;

	push(X_DOLLAR, &p_stack);


	p_stack_item = top(p_stack);
	stack_top_type = p_stack_item->type;
	input_type = type_of_token(p_token);

	do
	{

		switch(precedence_table[stack_top_type][input_type])
		{
			case('='):
			push(input_type, &p_stack);
			p_stack_item = top(p_stack);
			stack_top_type=p_stack_item->type;
			getToken(p_token);
			input_type = type_of_token(p_token);
			break;

			case('<'):
			top_to_handle(p_stack);
			push(input_type, &p_stack);
			p_stack_item = top(p_stack);
			stack_top_type=p_stack_item->type;
			getToken( p_token);
			input_type = type_of_token(p_token);
			break;
		
			case('>'):

	
			from_stack_to_handle(&(handle[0]), p_stack);
			if( rule(handle, &rule_id) )
			{
				remove_handle(&p_stack);
				push(X_NONTERMINAL, &p_stack);
				p_stack_item = top(p_stack);
				stack_top_type=p_stack_item->type;
			}
			else
			{
				return false;
			}
			break;

			case('x'):
			return false;
			break;
		}

	}
	while(input_type != X_DOLLAR || stack_top_type != X_DOLLAR);	
	return true;

}







ITEM_TYPE type_of_token(token_t *P_token)
// token je ukazatel na aktualni token
{
	switch(P_token->type)
	{	
		case T_PLUS:
		return X_PLUS;
		break;

		case T_MINUS:
		return X_MINUS;
		break;
		
		case T_MULTIPLICATION:
		return X_MULTIPLICATION;
		break;

		case T_DIVISION:
		return X_DIVISION;
		break;

		case T_LESS:
		return X_LESS;
		break;
		
		case T_GREATER:
		return X_GREATER;
		break;
		
		case T_LESS_EQUAL:
		return X_LESS_EQUAL;
		break;
		
		case T_GREATER_EQUAL:
		return X_GREATER_EQUAL;
		break;
		
		case T_EQUAL:
		return X_EQUAL;
		break;
		
		case T_NOT_EQUAL:
		return X_NOT_EQUAL;
		break;
		
		case T_L_BRACKET:
		return X_L_BRACKET;
		break;
		
		case T_R_BRACKET:
		return X_R_BRACKET;
		break;
		
		case T_ID:
		return X_I;
		break;

		case T_INT:
		return X_I;
		break;
		
		case T_FLOAT:
		return X_I;
		break;
		
		case T_STRING:
		return X_I;
		break;
		
		default:
		return X_DOLLAR;
	}


}


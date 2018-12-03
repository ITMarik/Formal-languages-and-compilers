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



bool start_handle(ITEM_TYPE type)
{
 	return (type == X_HANDLE_PLUS || type==X_HANDLE_MINUS || type==X_HANDLE_MULTIPLICATION ||
		type==X_HANDLE_DIVISION || type==X_HANDLE_LESS || type==X_HANDLE_GREATER ||
		type==X_HANDLE_LESS_EQUAL || type==X_HANDLE_GREATER_EQUAL || type==X_HANDLE_EQUAL ||
		type==X_HANDLE_NOT_EQUAL || type==X_HANDLE_L_BRACKET || type==X_HANDLE_I ||
		type==X_HANDLE_DOLLAR);
}



void from_stack_to_handle(ITEM_TYPE * pole, t_precedence_item *stack)
//nemeni stack
{
	printf("from_stack_to_handle\n");
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
		printf("start while\n");
		*pole = p_item->type;
		printf("ve stacku:%d v poli:%d icko je:%d pointer je:%p\n ",p_item->type, handle[i], i,pole);
		if( start_handle(handle[i]) )
		{
			printf("from stack to handle while if\n");
			pole++;
			*pole=X_STOP;
			printf("from stack to handle while end if\n");
			break;
		}
		p_item=p_item->next;
		i++;
		pole++;
		printf("from stack to handle end  while\n");
	}
}


bool rule(ITEM_TYPE handle[5], t_precedence_item * stack, int *rule_id )
{
	printf("rule\n");
	printf("handle [0]=%d  [1]=%d  [2]=%d  [3]=%d  [4]=%d \n",handle[0],handle[1],handle[2],handle[3],handle[4]);
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


ITEM_TYPE type_of_token(t_token *token)
// token je ukazatel na aktualni token
{
	switch(token->type)
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


void push(ITEM_TYPE type, t_precedence_item **top)
//funkce prida na vrchol zasobniku novy prvek s typem type
//pokud je pronter na stack NULL prida novy prvek
{
	printf("push:%d\n",type);
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





t_precedence_item *top(t_precedence_item * stack )
//vraci prvni neterminal ze stacku
{
	t_precedence_item * p_precedence_item = stack;

	while (p_precedence_item->type == X_NONTERMINAL)
	{
printf("while top\n");
		p_precedence_item = p_precedence_item->next;
	}
printf("konec top\n");
	return p_precedence_item;
}



void top_to_handle(t_precedence_item * stack )
//vraci prvni neterminal ze stacku
{
	t_precedence_item * p_precedence_item = stack;

	while (p_precedence_item->type == X_NONTERMINAL)
	{
printf("while toptohandle\n");
		p_precedence_item = p_precedence_item->next;
	}
printf("konec toptohandle\n");
	p_precedence_item-> type = (p_precedence_item->type +16);
}


void print_stack(t_precedence_item* pointer)
{
	while (pointer != NULL)
	{
		printf("stack:%d\n", pointer->type);
		pointer = pointer->next;
	}
}



#define table_size 14


typedef enum ITEM_TYPE
{
	X_PLUS,
	X_HANDLE_PLUS,
	X_MINUS,
	X_HANDLE_MINUS,
	X_MULTIPLICATION,
	S_HANDLE_MULTIPLICATION,
	X_DIVISION,
	X_HANDLE_DIVISION,
	X_LESS,
	X_HANDLE_LESS,
	X_GREATER,
	X_HANDLE_GREATER,
	X_LESS_EQUAL,
	X_HANDLE_LESSEQUAL,
	X_GREATER_EQUAL,
	X_HANDLE_GREATER_EQUAL,
	X_EQUAL,
	X_HANDLE_EQUAL,
	X_NOT_EQUAL,
	X_HANDLE_NOT_EQUAL,
	X_L_BRACKET,
	X_HANDLE_L_BRACKET,
	X_R_BRACKET,
	X_I,
	X_HANDLE_I,
	X_DOLLAR,

	X_NONTERMINAL,
	X_STOP

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



ITEM_TYPE handle[3]; //3 maximalni delka handle
//v poli bude handle reverzne


void from_stack_to_handle(ITEM_TYPE * handle, t_precedence_item *stack)
//nemeni stack
{
	printf("from_stack_to_handle\n");
	t_precedence_item *p_item = stack;
	int i = 0;
	while(i<=2)
	{
		*handle = p_item->type;
		if(handle[i] == X_HANDLE_PLUS || handle[i]==X_HANDLE_MINUS || handle[i]==S_HANDLE_MULTIPLICATION ||
		handle[i]==X_HANDLE_DIVISION || handle[i]==X_HANDLE_LESS || handle[i]==X_HANDLE_GREATER ||
		handle[i]==X_HANDLE_LESSEQUAL || handle[i]==X_HANDLE_GREATER_EQUAL || handle[i]==X_HANDLE_EQUAL ||
		handle[i]==X_HANDLE_NOT_EQUAL || handle[i]==X_HANDLE_L_BRACKET || handle[i]==X_HANDLE_I )
		{
			handle++;
			*handle=X_STOP;
			break;
		}
		p_item=p_item->next;
	i++;
	handle++;
	}
}


bool rule(ITEM_TYPE handle[3], t_precedence_item * stack, int *rule_id )
{
	printf("rule\n");
	if(handle[0]==X_HANDLE_I && handle[1]==X_STOP)
	{
	//pravidlo 1: E -> i
		*rule_id = 1;
		return true;
	}
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
	printf("konec push\n");	
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
printf("while top\n");
		p_precedence_item = p_precedence_item->next;
	}
printf("konec top\n");
	p_precedence_item-> type = (p_precedence_item->type +1);
}





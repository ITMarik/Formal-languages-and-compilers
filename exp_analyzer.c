#include "exp_analyzer.h"










bool expression(int * ToKeN_OrDeR, t_token *p_token)
{
	
	printf("\n\n funkce expression: true\n\n");
	int rule_id;
	t_precedence_item *p_stack_item;
	t_precedence_item * p_stack = NULL;
	ITEM_TYPE stack_top_type, input_type;

	push(X_DOLLAR, &p_stack);

	do
	{
		p_stack_item = top(p_stack);
		stack_top_type = p_stack_item->type;
		input_type = type_of_token(p_token);
		printf("do while\n");
		switch(precedence_table[stack_top_type][input_type])
		{
			case('='):
			printf("jsem v case =\n");
			push(input_type, &p_stack);
			next_token(ToKeN_OrDeR, p_token);
			input_type = type_of_token(p_token);
			break;

			case('<'):
			printf("jsem v case =\n");
			top_to_handle(p_stack);
			push(input_type, &p_stack);
			next_token(ToKeN_OrDeR, p_token);
			input_type = type_of_token(p_token);
			break;
		
			case('>'):
			printf("jsem v case >\n");
			from_stack_to_handle(&(handle[0]), p_stack);
			if( rule(handle, p_stack, &rule_id) )
			{
				printf("\n\n\n!!!!\npravidlo:%d\n", rule_id);
			}
			else
			{
				printf("neplatny handel\n");
				return false;
			}
			break;

			case('x'):
			printf("jsem v case x\n");
			return false;
			break;

			default:
			printf("jj\n");
		}

	}
	while(input_type == X_DOLLAR && stack_top_type == X_DOLLAR);
	
	return true;

  printf("%c\n",precedence_table[stack_top_type][input_type]);

	next_token(ToKeN_OrDeR, p_token);//demo nebude tu 
}










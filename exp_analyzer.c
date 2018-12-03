#include "exp_analyzer.h"










bool expression(int * ToKeN_OrDeR, t_token *p_token)
{
	
	printf("\n\n funkce expression\n\n");
	int rule_id;
	t_precedence_item *p_stack_item;
	t_precedence_item * p_stack = NULL;
	ITEM_TYPE stack_top_type, input_type;

	push(X_DOLLAR, &p_stack);


	p_stack_item = top(p_stack);
	stack_top_type = p_stack_item->type;
	input_type = type_of_token(p_token);
	printf("input_type:%d\n",input_type);

	do
	{
		printf("do while\n");
		switch(precedence_table[stack_top_type][input_type])
		{
			case('='):
			printf("jsem v case =\n");
			printf("HH_%d,%d_HH\n",stack_top_type,input_type);
  			printf("XX_%c_XX\n",precedence_table[stack_top_type][input_type]);
			push(input_type, &p_stack);
			p_stack_item = top(p_stack);
			stack_top_type=p_stack_item->type;
			next_token(ToKeN_OrDeR, p_token);
			input_type = type_of_token(p_token);
			printf("input_type:%d\n",input_type);
			break;

			case('<'):
			printf("jsem v case <\n");
			print_stack(p_stack);
			printf("HH_%d,%d_HH\n",stack_top_type,input_type);
			top_to_handle(p_stack);
			push(input_type, &p_stack);
			p_stack_item = top(p_stack);
			stack_top_type=p_stack_item->type;
			next_token(ToKeN_OrDeR, p_token);
			input_type = type_of_token(p_token);
			printf("input_type:%d\n",input_type);
			break;
		
			case('>'):
			printf("jsem v case >\n");
			printf("HH_%d,%d_HH\n",stack_top_type,input_type);
		print_stack(p_stack);
			from_stack_to_handle(&(handle[0]), p_stack);
			if( rule(handle, p_stack, &rule_id) )
			{
				printf("\n\n\n!!!!\npravidlo:%d\n", rule_id);
			print_stack(p_stack);
				remove_handle(&p_stack);
				printf("ODSTRANIL SE HANDE\n");
			print_stack(p_stack);
				push(X_NONTERMINAL, &p_stack);
			print_stack(p_stack);
				p_stack_item = top(p_stack);
				stack_top_type=p_stack_item->type;
			}
			else
			{
				printf("!!!!!FALSE case > neplatny handel\n");
				return false;
			}
			break;

			case('x'):
			printf("!!!!!FALSE case x\n");
			return false;
			break;

			default:
			printf("!!!!!!!!!!!!JSEM V DEFAULT\n");
		}

	}
	while(input_type != X_DOLLAR || stack_top_type != X_DOLLAR);
printf("!!!koonec while expression vraci true!!\n");	
	return true;

}

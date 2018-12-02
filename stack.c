
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void stack_t_init(stack_t* stack)
{
    if (!(stack = (stack_t*)malloc(sizeof)(stack_t)))
        printf("Error\n");

    stack->top =  NULL;
}

void stack_push(stack_t* stack, void *data) {
    stack_i* new_item = (stack_i*)malloc(sizeof(stack_i));

    if (new_item == NULL)
        return false;

    new_item->data_type = data;
    new_item->next = stack->top;
    stack->top = new_item;

    //return true;
}


void stackPop(stack_t *stack) {

    if (stack->top != NULL )
        stack->top = s->top->next;
}

void stack_top(stack_t* stack)
{
    return  stack->top->data_type;
}

void stack_t_free(stack_t* stack)
{
    while(stack_t_pull(stack));
}
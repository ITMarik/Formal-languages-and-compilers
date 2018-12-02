#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack_i
{
    void *data_type;
    struct stack_i *next;
} stack_i;

typedef struct stack
{
	stack_i *top;
} stack_t;



void stack_t_init(stack_t* stack);

void stack_push(stack_t* stack, void *data_type);

void stackPop(stack_t *stack);

void stack_top(stack_t* stack);

void stack_free(stack_t* stack);

#endif //IFJ 2018 stack_H
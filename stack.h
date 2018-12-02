#ifndef stack_t_LIBRARY_H
#define stack_t_LIBRARY_H

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

bool stack_push(stack_t* stack, void *data_type);

void stack_top(stack_t* stack);

void stack_t_free(stack_t* stack);

#endif //IFJ 2018 stack_H
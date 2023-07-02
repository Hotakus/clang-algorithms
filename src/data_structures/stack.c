/**
  ******************************************************************************
  * @file      : stack.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/24
  ******************************************************************************
  */

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "../config.h"

#define FIRST_LAYER_NAME "first_element"

stack_t *stack_create(char *desc) {
    stack_t *_stack = (stack_t *) calloc(1, sizeof(stack_t));
    _stack->top = (stack_elem_t *) calloc(1, sizeof(stack_elem_t));
    _stack->depth = 0;

    _stack->top->name = FIRST_LAYER_NAME;

    return _stack;
}


void stack_destroy(stack_t *stack) {
    while (stack->depth)
        stack_elem_destroy(stack_pop(stack));

    free(stack->top);
    free(stack);
}


stack_elem_t *stack_push(stack_t *stack, stack_elem_t *stack_elem) {
    if (stack_elem == NULL)
        stack_elem = stack_elem_create(NULL, NULL);
    stack_elem->down = stack->top;
    stack->top = stack_elem;
    stack->depth += 1;
    return stack_elem;
}


stack_elem_t *stack_pop(stack_t *stack) {
    if (BA_STRCMP(stack->top->name, FIRST_LAYER_NAME) == 0) {
        return NULL;
    }
    stack_elem_t *tmp = stack->top;
    stack->top = stack->top->down;
    stack->depth -= 1;
    return tmp;
}


stack_elem_t *stack_elem_create(char *name, void *value) {
    stack_elem_t *stack_elem = (stack_elem_t *) calloc(1, sizeof(stack_elem_t));
    stack_elem->name = name;
    stack_elem->data = value;
    return stack_elem;
}

void stack_elem_destroy(stack_elem_t *elem) {
    free(elem);
}

void stack_test() {
    stack_t *stack = stack_create(NULL);

    for (int i = 0; i < 1000000; ++i) {
        stack_push(stack, stack_elem_create("s1", NULL));
        stack_push(stack, stack_elem_create("s2", NULL));
        stack_push(stack, stack_elem_create("s3", NULL));
        stack_push(stack, stack_elem_create("s4", NULL));

        for (int i = 0; i < 4; ++i) {
            stack_elem_t *elem = stack_pop(stack);
            //printf("[%d] top name: %s\n", i + 1, elem->name);
            stack_elem_destroy(elem);
        }
    }

    stack_destroy(stack);
}

/**
  ******************************************************************************
  * @file      : stack.h
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/24
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_STACK_H
#define CODEWAR_KATA_C_STACK_H

#include "chain.h"

typedef struct stack_elem_t stack_elem_t;
typedef struct stack_elem_t {
    char *name;
    void *value;
    stack_elem_t *down;
} stack_elem_t;

typedef struct STACK_T {
    size_t depth;
    stack_elem_t *top;
} stack_t;

#ifdef __cplusplus
extern "C" {
#endif


stack_t *stack_create(char *desc);
void stack_destroy(stack_t *stack);

stack_elem_t *stack_append(stack_t *stack, stack_elem_t *stack_elem);
stack_elem_t *stack_pop(stack_t *stack);
stack_elem_t *elem_create(char *name, void *value);
void elem_destroy(stack_elem_t *elem);

void stack_test();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_STACK_H

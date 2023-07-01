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

typedef struct stack_elem_t stack_elem_t;
typedef struct stack_elem_t {
    char *name;
    void *data;
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

stack_elem_t *stack_push(stack_t *stack, stack_elem_t *stack_elem);
stack_elem_t *stack_pop(stack_t *stack);
stack_elem_t *stack_elem_create(char *name, void *value);
void stack_elem_destroy(stack_elem_t *elem);

void stack_test();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_STACK_H

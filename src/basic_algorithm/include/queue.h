/**
  ******************************************************************************
  * @file           : queue.h
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/6/30
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_QUEUE_H
#define CODEWAR_KATA_C_QUEUE_H

#include <stddef.h>
#include "chain.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queue_node_t queue_node_t;

typedef struct queue_node_t {
    const char *name;
    void *data;
} queue_node_t;

typedef struct queue_t {
    char *desc;
    size_t waiting;
    chain_t *_chain;
} queue_t;

queue_t *queue_create(char *desc);
void queue_destroy(queue_t *queue);

queue_node_t *queue_node_create(const char *name, void *data);
void queue_node_destroy(queue_node_t *node);

void queue_push(queue_t *queue, const char *name, void *data);
queue_node_t queue_pop(queue_t *queue);

void queue_test();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //CODEWAR_KATA_C_QUEUE_H

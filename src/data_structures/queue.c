/**
  ******************************************************************************
  * @file           : queue.c
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/6/30
  ******************************************************************************
  */

#include <stdio.h>
#include "include/queue.h"

queue_t *queue_create(char *desc) {
    queue_t *queue = (queue_t *) calloc(1, sizeof(queue_t));
    queue->_chain = chain_create(desc);
    queue->desc = desc;
    queue->waiting = 0;
    return queue;
}

void queue_destroy(queue_t *queue) {
    chain_destroy(queue->_chain);
    free(queue);
}

void queue_push(queue_t *queue, const char *name, void *data) {
    if (!queue) return;

    chain_t *chain = queue->_chain;
    chain_node_t *cn = chain->node_new(name, data);
    chain->insert(chain, cn, "head", false);

    queue->waiting += 1;
}

queue_node_t queue_pop(queue_t *queue) {
    chain_node_t *prev = queue->_chain->tail->prev_node;
    queue_node_t node;
    node.name = prev->name;
    node.data = prev->data;

    if (prev != queue->_chain->head)
        queue->_chain->rm_node(queue->_chain, prev->name, prev);

    queue->waiting -= 1;
    return node;
}


void queue_test() {
    queue_t *queue = queue_create("queue test");

    int sum = 114513;

    queue_node_t node = {
            .name = "node 1",
            .data = &sum
    };
    queue_push(queue, node.name, node.data);

    for (int i = 0; i < 5; ++i) {
        queue_push(queue, node.name, node.data);
    }


    for (int i = 0; i < 3; ++i) {
        queue_node_t node2 = queue_pop(queue);
        printf("pop name : %s; data: %d\n", node2.name, *(int *) (node2.data));
    }


    queue->_chain->poll(queue->_chain, true);

    printf("\n%s\n", queue->_chain->desc);
    printf("%d\n", queue->waiting);

    queue_destroy(queue);
}

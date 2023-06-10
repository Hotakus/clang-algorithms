#include <malloc.h>
#include <stdio.h>
#include "chain.h"
#include "rand_gen.h"
#include "utilities.h"

#define DEBUG 1


chain_node_t *node_create(chain_t *chain) {
    chain_node_t *node = (chain_node_t *) calloc(1, sizeof(chain_node_t));

    if (node == NULL) {
#if DEBUG == 1
        printf("node_create: allocated failed\n");
#endif
        return NULL;
    }

    node->prev_node = NULL;
    node->next_node = NULL;
    node->value = NULL;

    chain->length++;
    node->id = chain->length;

    return node;
}


void node_destroy(chain_node_t *node) {
    if (node == NULL) {
#if DEBUG == 1
        printf("node_destroy: node is NULL\n");
#endif // DEBUG
    }

#if DEBUG == 1
    printf("destroy node id - %zu\n", node->id);
#endif // DEBUG

    free(node);
    node = NULL;
}


void chain_remove_node_by_id(chain_t *chain, const size_t id) {
    chain_node_t *probe = chain->head->next_node;
    while (probe != chain->tail) {

    }
}


/**
 * Create a chain
 * @param desc
 * @return
 */
chain_t *chain_create(char *desc) {
    chain_t *chain = (chain_t *) calloc(1, sizeof(chain_t));

    chain->length = 0;  // head and tail
    chain->chain_desc = desc;  // chain description (Maybe empty)
    chain->is_loop = false;

    // create head and tail nodes.
    chain->head = node_create(chain);
    chain->tail = node_create(chain);

    chain->head->prev_node = NULL;
    chain->head->next_node = chain->tail;
    chain->tail->prev_node = chain->head;
    chain->tail->next_node = NULL;

    return chain;
}


void chain_destroy(chain_t *chain) {
    if (chain == NULL) {
#if DEBUG == 1
        printf("chain_destroy: chain is NULL\n");
#endif // DEBUG
        return;
    }

    chain_remove_all(chain);
    free(chain);
    chain = NULL;
}


void chain_remove_all(chain_t *chain) {
    chain_node_t *probe = chain->head->next_node;
    while (probe != chain->tail->next_node) {
        node_destroy(probe->prev_node);
        probe = probe->next_node;
    }
    node_destroy(chain->tail);
}


void chain_append(chain_t *chain, chain_node_t *node) {
    if (chain == NULL || node == NULL) {
#if DEBUG == 1
        printf("chain_append: chain or node is NULL\n");
#endif // DEBUG
        return;
    }

    if (chain->is_loop) {
        // TODO: is loop
    } else {
        chain->tail->next_node = node;
        node->prev_node = chain->tail;
        chain->tail = node;
    }
}


void chain_poll(chain_t *chain) {
    if (chain->head == chain->tail) {
#if DEBUG == 1
        printf("chain_poll: only one chain is exists\n");
#endif // DEBUG
        return;
    }

#if DEBUG == 1
    chain_node_t *probe = chain->head;
    while (probe != chain->tail->next_node) {
        printf("%zu | %s\n", probe->id, (char *)probe->value);
        probe = probe->next_node;
    }
#endif // DEBUG
}


void chain_test() {
    chain_t *chain = chain_create("First chain");


    for (int i = 0; i < 8; ++i) {
        chain_append(chain, node_create(chain));
    }

    chain_poll(chain);

    // printf("p: %zu | %s\n", ((chain_node_t*)chain->tail->prev_node)->id, (char *)((chain_node_t*)chain->tail->prev_node)->value);
    chain_destroy(chain);
}




#include <malloc.h>
#include <stdio.h>
#include "chain.h"
#include "rand_gen.h"
#include "utilities.h"

#define DEBUG 1


static chain_node_t *create_node(chain_t *chain);
static void destroy_node(chain_node_t *node);
static int get_chain_max_id(chain_t *chain);

chain_node_t *create_node(chain_t *chain) {
    chain_node_t *node = (chain_node_t *) calloc(1, sizeof(chain_node_t));
    node->prev_node = NULL;
    node->next_node = NULL;
    node->value = NULL;

    chain->chain_length++;
    node->id = chain->chain_length;

    return node;
}

void destroy_node(chain_node_t *node) {
    if (node == NULL) {
#if DEBUG == 1
        printf("destroy_node: node is NULL\n");
#endif // DEBUG
    }

    free(node);
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

    chain->chain_length = 0;  // head and tail
    chain->chain_desc = desc;  // chain description (Maybe empty)
    chain->is_loop = false;

    // create head and tail nodes.
    chain->head = create_node(chain);
    chain->tail = create_node(chain);

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
}


void chain_remove_all(chain_t *chain) {

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
        node->next_node = NULL;
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

    chain->tail->value = "hotakus";
    //printf("%zu | %s\n", chain->tail->id, (char *)chain->tail->value);

    chain_append(chain, create_node(chain));
    chain->tail->value = "trisuborn";
    chain_append(chain, create_node(chain));
    chain->tail->value = "trisuborn2";

    chain_poll(chain);

    printf("p: %zu | %s\n", ((chain_node_t*)chain->tail->prev_node)->id, (char *)((chain_node_t*)chain->tail->prev_node)->value);
    //printf("%zu\n", chain->tail->id);

    free(chain);
}




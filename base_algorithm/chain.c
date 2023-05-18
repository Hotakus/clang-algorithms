#include <malloc.h>
#include <stdio.h>
#include "chain.h"
#include "rand_gen.h"
#include "utilities.h"

#define DEBUG 0


static chain_node_t *create_node();


/**
 * Create a chain
 * @param desc
 * @param enable_loop
 * @return
 */
chain_t *chain_create(char *desc, bool enable_loop) {
    chain_t *chain = (chain_t *) malloc(sizeof(chain_t));

    chain->chain_length = 1;  // only head.
    chain->chain_desc = desc;  // chain description
    chain->chain_is_loop = enable_loop;  // whether loop

    // allocate memory for head and tail
    chain_node_t *head = (chain_node_t *) malloc(sizeof(chain_node_t));
    chain_node_t *tail = (chain_node_t *) malloc(sizeof(chain_node_t));
    chain->head = head;
    chain->tail = tail;

    // whether loop
    if (enable_loop) {
        head->prev_node = tail;
        head->next_node = tail;

        tail->prev_node = head;
        tail->next_node = head;
    } else {
        head->prev_node = NULL;
        tail->next_node = NULL;
    }

    return chain;
}


void chain_destroy(chain_t *chain) {
    if (chain == NULL) {
#if DEBUG == 0
        printf("chain_destroy: chain is NULL\n");
#endif // DEBUG
        return;
    }

    chain_remove_all(chain);
    free(chain);
}


void chain_remove_all(chain_t *chain) {

}


chain_node_t *create_node() {

    chain_node_t *node = (chain_node_t *) malloc(sizeof(chain_node_t));
    node->prev_node = NULL;
    node->next_node = NULL;
    node->value = NULL;

    char *tmp = calloc(11, sizeof(char));
    num_to_string(tmp, rand_gen(11));
    node->id = tmp;

    return node;
}


void chain_append(chain_t *chain, const char *value) {
    if (chain == NULL) {
#if DEBUG == 0
        printf("chain_append: chain is NULL\n");
#endif // DEBUG
        return;
    }


}




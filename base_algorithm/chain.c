#include <malloc.h>
#include "chain.h"

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
    if (chain == NULL) return;
    chain_remove_all(chain);
    free(chain);
}

void chain_remove_all(chain_t *chain) {

}




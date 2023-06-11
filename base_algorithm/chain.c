
#include <stdlib.h>
#include "chain.h"
#include "utilities.h"

#define DEBUG 1

#if DEBUG == 1
#include <stdio.h>
#endif

#if CHAIN_USE_SEM == 1
#include <semaphore.h>
#endif

chain_node_t *node_create(chain_t *chain, const char *name) {
    chain_node_t *node = (chain_node_t *) calloc(1, sizeof(chain_node_t));

    if (node == NULL) {
#if DEBUG == 1
        printf("%s: allocated failed in %s\n", __FUNCTION__, __FILE__);
#endif
        return NULL;
    }

    node->name = name;

    node->prev_node = NULL;
    node->next_node = NULL;
    node->value = NULL;

#if CHAIN_USE_SEM == 1
    int sem_res = sem_wait(chain->nc_sem);
    if (sem_res != 0) {
#if DEBUG == 1
        printf("%s: failed %s\n", __FUNCTION__, __FILE__);
#endif // DEBUG
        free(node);
        node = NULL;
        return node;
    }
#endif

    chain->length++;
    node->id = chain->length;

#if CHAIN_USE_SEM == 1
    sem_post(chain->nc_sem);
#endif

    return node;
}


void node_destroy(chain_node_t *node) {
    if (node == NULL) {
#if DEBUG == 1
        printf("%s: node is NULL in %s\n", __FUNCTION__, __FILE__);
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
    chain->head = node_create(chain, "head");
    chain->tail = node_create(chain, "tail");

    chain->head->prev_node = NULL;
    chain->head->next_node = chain->tail;
    chain->tail->prev_node = chain->head;
    chain->tail->next_node = NULL;

#if CHAIN_USE_SEM == 1
    int sem_res = sem_init(chain->nc_sem, 0, 1);
    if (sem_res != 0) {
#if DEBUG == 1
        printf("%s: creating semaphore of chain failed in %s\n", __FUNCTION__, __FILE__);
#endif // DEBUG
        return NULL;
    }
#endif

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

    // TODO: change tail name;
    if (chain->is_loop) {
        // TODO: is loop
    } else {
        chain->tail->next_node = node;
        node->prev_node = chain->tail;
        chain->tail = node;
    }
}


chain_node_t *chain_find_node_by_name(chain_t *chain, const char *name) {
    chain_node_t *probe = chain->head;
    while (probe != chain->tail->next_node) {
        if (str_cmp(probe->name, name) != 0) {
            probe = probe->next_node;
            continue;
        }
        break;
    }
    return probe;
}


/**
 * 将node插入chain的指定位置
 * @param chain 要操作的链表
 * @param node 要插入的node
 * @param name 要插入哪个node，这是要插入node的名字
 * @param front 如果true，则插入前面。如果false，则插入后面
 */
void chain_node_insert(chain_t *chain, chain_node_t *node, const char *name, bool front) {
    chain_node_t *dst = chain_find_node_by_name(chain, name);
    chain_node_t *dst_delta = NULL;

    if (front) {
        dst_delta = dst->prev_node;
        dst_delta->next_node = node;

        node->prev_node = dst_delta;
        node->next_node = dst;

        dst->prev_node = node;
    } else {
        if (dst == chain->tail) {
            chain_append(chain, node);
            return;
        }
        dst_delta = dst->next_node;
        dst_delta->prev_node = node;

        node->next_node = dst_delta;
        node->prev_node = dst;

        dst->next_node = node;
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
        printf("%s \t %zu \t %s \n", probe->name, probe->id, (char *) probe->value);
        probe = probe->next_node;
    }
#endif // DEBUG
}


void chain_test() {
    chain_t *chain = chain_create("First chain");

    chain_node_insert(chain, node_create(chain, "tnode"), "tail", true);
    chain_node_insert(chain, node_create(chain, "tnode2"), "tail", false);

    chain_poll(chain);

    // printf("p: %zu | %s\n", ((chain_node_t*)chain->tail->prev_node)->id, (char *)((chain_node_t*)chain->tail->prev_node)->value);
    chain_destroy(chain);
}

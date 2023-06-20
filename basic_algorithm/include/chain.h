#ifndef CODEWAR_KATA_C_CHAIN_H
#define CODEWAR_KATA_C_CHAIN_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../config.h"

#if USE_CHAIN_SEM == 1
#include <semaphore.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct chain_node_t {
    size_t id;
    const char *name;
    void *value;
    void *prev_node;
    void *next_node;
} chain_node_t;

typedef struct {
    size_t length;
    chain_node_t *junction_node;
    chain_node_t *end_node;
} chain_loop_info_t;


typedef struct chain_t {
    size_t length;
    char *desc;

#if USE_CHAIN_SEM == 1
    sem_t *nc_sem;  // node create semaphore
#endif

    // 当前链表是否为环（不是是否包含环，判断是否包含环，用 chain_has_loop 函数）
    bool is_loop;

    // 是否包含环
    bool has_loop;
    chain_loop_info_t *loop_info;

    chain_node_t* head;
    chain_node_t* tail;
} chain_t;


chain_t *chain_create(char *desc);
void chain_destroy(chain_t *chain);
void chain_poll(chain_t *chain, bool forward);
void chain_flush(chain_t *chain);

chain_node_t *node_create(chain_t *chain, const char *name);
void node_destroy(chain_node_t *node);
void node_connect(chain_node_t *dst_node, chain_node_t *src_node, bool front);
void nodes_swap(chain_node_t *dst_node, chain_node_t *src_node);

void chain_append(chain_t *chain, chain_node_t *node);
void chain_node_insert(chain_t *chain, chain_node_t *node, const char *name, bool front);
chain_node_t *chain_find_node_by_name(chain_t *chain, const char *name);

void chain_remove_node_by_name(chain_t *chain, const char *name);
void chain_remove_all(chain_t *chain);

// extra functions
bool chain_has_loop(chain_t *chain, bool detach);
chain_node_t *determine_junction_node(chain_t *chain, chain_node_t *collision_node);
int chain_loop_length(chain_node_t *collision_node);
chain_node_t *get_loop_end_node(chain_t *chain);

void chain_test();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_CHAIN_H

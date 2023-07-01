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

/* pre typedef */
typedef struct chain_t chain_t;
typedef struct chain_node_t chain_node_t;


/* functions typedef */
typedef void (chain_poll_func_t)(chain_t *chain, bool forward);
typedef chain_node_t *(node_create_func_t)(chain_t *chain, const char *name);
typedef void (chain_node_destroy_func_t)(chain_node_t *node);
typedef void (chain_node_connect_func_t)(chain_node_t *dst_node, chain_node_t *src_node, bool front);
typedef void (chain_node_swap_t)(chain_node_t *dst_node, chain_node_t *src_node);

typedef void (chain_append_func_t)(chain_t *chain, chain_node_t *node);
typedef chain_node_t * (chain_pop_func_t)(chain_t *chain);
typedef void (chain_node_insert_func_t)(chain_t *chain, chain_node_t *node, const char *name, bool front);
typedef chain_node_t *(chain_find_node_by_name_func_t)(chain_t *chain, const char *name, bool forward);
typedef void (chain_remove_node_func_t)(chain_t *chain, const char *name, chain_node_t *node);
typedef void (chain_remove_all_func_t)(chain_t *chain);

typedef bool (chain_has_loop_t)(chain_t *chain, bool detach);
typedef chain_node_t *(get_loop_end_node_t)(chain_t *chain);


/* typedef */
typedef struct chain_node_t {
    size_t id;
    const char *name;
    void *data;
    chain_node_t *prev_node;
    chain_node_t *next_node;
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

    // functions
    struct {
        chain_poll_func_t *poll;
        node_create_func_t *node_new;
        chain_node_destroy_func_t *node_del;
        chain_node_connect_func_t *node_conn;
        chain_node_swap_t *node_swap;

        chain_append_func_t *append;
        chain_pop_func_t *pop;
        chain_node_insert_func_t *insert;
        chain_find_node_by_name_func_t *find_node;
        chain_remove_node_func_t *rm_node;
        chain_remove_all_func_t *rm_all_nodes;

        chain_has_loop_t *check_loop;
        get_loop_end_node_t *get_loop_end;
    };

} chain_t;


/* prototypes */
chain_t *chain_create(char *desc);
void chain_destroy(chain_t *chain);
void chain_flush(chain_t *chain);
// extra functions
// miscellaneous
chain_t *chain_merge(chain_t *chain1, chain_t *chain2);


void chain_test();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_CHAIN_H

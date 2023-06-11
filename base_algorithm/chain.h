#ifndef CODEWAR_KATA_C_CHAIN_H
#define CODEWAR_KATA_C_CHAIN_H

#include <stdint.h>
#include <stdbool.h>

#define CHAIN_USE_SEM 0

#if CHAIN_USE_SEM == 1
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

typedef struct chain_t {
    size_t length;
    char *chain_desc;

#if CHAIN_USE_SEM == 1
    sem_t *nc_sem;  // node create semaphore
#endif

    bool is_loop;

    chain_node_t* head;
    chain_node_t* tail;
} chain_t;


chain_t *chain_create(char *desc);
void chain_destroy(chain_t *chain);
void chain_poll(chain_t *chain);
void chain_flush(chain_t *chain);

chain_node_t *node_create(chain_t *chain, const char *name);
void node_destroy(chain_node_t *node);

void chain_append(chain_t *chain, chain_node_t *node);
void chain_node_insert_front(chain_t *chain, size_t id);
chain_node_t *chain_find_node_by_name(chain_t *chain, const char *name);

void chain_remove_node_by_id(chain_t *chain, size_t id);
void chain_remove_all(chain_t *chain);
void chain_remove_head(chain_t *chain);
void chain_remove_tail(chain_t *chain);

void chain_test();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_CHAIN_H

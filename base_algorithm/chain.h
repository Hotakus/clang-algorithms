#ifndef CODEWAR_KATA_C_CHAIN_H
#define CODEWAR_KATA_C_CHAIN_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct chain_node_t {
    char *id;
    void *value;
    void *prev_node;
    void *next_node;
} chain_node_t;

typedef struct chain_t {
    size_t chain_length;
    char *chain_desc;

    bool chain_is_loop;
    chain_node_t* head;
    chain_node_t* tail;
} chain_t;

chain_t *chain_create(char *desc, bool enable_loop);
void chain_destroy(chain_t *chain);

void chain_append(chain_t *chain, const char *value);
void chain_insert(chain_t *chain, size_t id);
chain_node_t *chain_find_by_id(chain_t *chain, const char *id);

void chain_remove_by_id(chain_t *chain, const char *id);
void chain_remove_all(chain_t *chain);
void chain_remove_head(chain_t *chain);
void chain_remove_tail(chain_t *chain);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_CHAIN_H

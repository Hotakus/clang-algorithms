#include <stdlib.h>
#include "include/chain.h"
#include "include/utilities.h"

#if DEBUG == 1
#include <stdio.h>
#endif

#if USE_CHAIN_SEM == 1
#include <semaphore.h>
#endif


void _node_step(chain_node_t *node, int steps, bool forward);


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

#if USE_CHAIN_SEM == 1
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

#if USE_CHAIN_SEM == 1
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


/**
 * Create a chain
 * @param desc
 * @return
 */
chain_t *chain_create(char *desc) {
    chain_t *chain = (chain_t *) calloc(1, sizeof(chain_t));

    chain->length = 0;  // head and tail
    chain->desc = desc;  // chain description (Maybe empty)
    chain->is_loop = false;

    // create head and tail nodes.
    chain->head = node_create(chain, "head");
    chain->tail = node_create(chain, "_");

    chain->head->prev_node = NULL;
    chain->head->next_node = chain->tail;
    chain->tail->prev_node = chain->head;
    chain->tail->next_node = NULL;

#if USE_CHAIN_SEM == 1
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
    node_destroy(chain->head);
    node_destroy(chain->tail);

    if (chain->has_loop) {
        free(chain->loop_info);
        chain->loop_info = NULL;
    }

    free(chain);
    chain = NULL;
}


/**
 * remove所有node，不包括头尾
 * @param chain
 */
void chain_remove_all(chain_t *chain) {
    if (chain->length == 2) {
        return;
    }

    chain_node_t *probe = ((chain_node_t *) chain->head->next_node)->next_node;
    while (probe != chain->tail->next_node) {
        node_destroy(probe->prev_node);
        probe = probe->next_node;
    }

    chain->head->next_node = chain->tail;
    chain->tail->prev_node = chain->head;
}


/**
 * append 一个node
 * @param chain 要操作的链表
 * @param node 要插入的node
 */
void chain_append(chain_t *chain, chain_node_t *node) {
    if (chain == NULL || node == NULL) {
#if DEBUG == 1
        printf("chain_append: chain or node is NULL\n");
#endif // DEBUG
        return;
    }

    // change tail
    // TODO: change tail name;
    if (chain->is_loop) {
        // TODO: is loop
    } else {
        chain->tail->next_node = node;
        node->prev_node = chain->tail;
        chain->tail = node;
    }
}


/**
 * 根据name在chain中找到node并返回
 * @param chain 要操作的链表
 * @param name 要找的node的名字
 * @return node
 */
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


void chain_poll(chain_t *chain, bool forward) {
    if (chain->head == chain->tail) {
#if DEBUG == 1
        printf("chain_poll: only one chain is exists\n");
#endif // DEBUG
        return;
    }

    // TODO: has loop
#if DEBUG == 1
    if (forward) {
        chain_node_t *probe = chain->head;
        printf("chain_poll: forward\n");
        while (probe != chain->tail->next_node) {
            printf("%s \t %zu \t %s \n", probe->name, probe->id, (char *) probe->value);
            probe = probe->next_node;
        }
    } else {
        chain_node_t *probe = chain->tail;
        printf("chain_poll: backward\n");
        while (probe != chain->head->prev_node) {
            printf("%s \t %zu \t %s \n", probe->name, probe->id, (char *) probe->value);
            probe = probe->prev_node;
        }
    }
#endif // DEBUG
}


/**
 * 根据node的name从链表移除并销毁
 * @param chain 要操作的链表
 * @param name node的名字
 */
void chain_remove_node_by_name(chain_t *chain, const char *name) {
    chain_node_t *node = chain_find_node_by_name(chain, name);
    chain_node_t *p_node = node->prev_node;
    chain_node_t *n_node = node->next_node;

    node_connect(p_node, n_node, false);

    node_destroy(node);
}


/**
 * 将src node连接到dst node的前面或后面
 * @param dst_node 目标node
 * @param src_node 源node
 * @param front 连接到前面还是后面
 */
void node_connect(chain_node_t *dst_node, chain_node_t *src_node, bool front) {
    if (front) {
        dst_node->prev_node = src_node;
        src_node->next_node = dst_node;
    } else {
        dst_node->next_node = src_node;
        src_node->prev_node = dst_node;
    }
}


void nodes_swap(chain_node_t *dst_node, chain_node_t *src_node) {
    chain_node_t *dst_prev_node = dst_node->prev_node;
    chain_node_t *dst_next_node = dst_node->next_node;

    chain_node_t *src_prev_node = src_node->prev_node;
    chain_node_t *src_next_node = src_node->next_node;


}


void _node_step(chain_node_t *node, int steps, bool forward) {
    for (unsigned char step = 0; step < steps; step += 1) {
        if (node->next_node == NULL)
            return;

        if (forward)
            node = node->next_node;
        else
            node = node->prev_node;
    }
}


/**
 * 判断链表是否含环，是否将环断开
 * @param chain 要操作的链表
 * @param detach 是否detach
 * @return 是否含含环，若detach == true，则返回false
 */
bool chain_has_loop(chain_t *chain, bool detach) {
    chain_node_t *slow = chain->head;
    chain_node_t *fast = chain->head;
    unsigned char fast_step = 2;  // 步进
    unsigned char slow_step = 1;

    while (fast->next_node != NULL) {
        _node_step(fast, fast_step, true);
        _node_step(slow, slow_step, true);

        if (fast == slow) {
            // TODO: determine junction
            chain_node_t *junction = determine_junction_node(chain);

            if (detach) {
                chain->has_loop = false;
                return false;
            }

            chain->has_loop = true;

            if (chain->loop_info == NULL)
                chain->loop_info = (chain_loop_info_t *) calloc(1, sizeof(chain_loop_info_t));
            chain->loop_info->length = chain_loop_length(chain, fast);
            chain->loop_info->junction_node = junction;

            return true;
        }
    }

    return false;
}


int chain_loop_length(chain_t *chain, chain_node_t *collision_node) {
    chain_node_t *slow = chain->head;
    chain_node_t *fast = chain->head;
    return 0;
}


chain_node_t *determine_junction_node(chain_t *chain) {

    return NULL;
}


void chain_flush(chain_t *chain) {

}


void chain_test() {
    chain_t *chain = chain_create("First chain");

    chain_node_insert(chain, node_create(chain, "tnode"), "_", true);
    chain_node_insert(chain, node_create(chain, "tnode2"), "_", false);
    chain_node_insert(chain, node_create(chain, "tnode3"), "_", false);

    chain_poll(chain, true);

    chain->tail->next_node = chain_find_node_by_name(chain, "_");

    printf("chain_has_loop: %d\n", chain_has_loop(chain, false));


    // printf("p: %zu | %s\n", ((chain_node_t*)chain->tail->prev_node)->id, (char *)((chain_node_t*)chain->tail->prev_node)->value);
    // chain_destroy(chain);
}




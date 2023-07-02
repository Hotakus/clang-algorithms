/**
  ******************************************************************************
  * @file           : hash_table_create.h
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/7/2
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_HASH_TABLE_H
#define CODEWAR_KATA_C_HASH_TABLE_H

#include "hash.h"
#include "chain.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef chain_t hash_table_collision_entry_t;
typedef chain_node_t ht_key_value_t;

typedef struct hash_table_t hash_table_t;
typedef struct hash_table_entry_t hash_table_entry_t;

typedef int (hash_table_put_t)(hash_table_t *ht, char *key, void *value);
typedef ht_key_value_t *(hash_table_get_t)(hash_table_t *ht, char *key);
typedef void (hash_table_remove_t)(hash_table_t *ht, char *key);
typedef void (hash_table_rehash_t)(hash_table_t *ht);
typedef void (hash_table_clear_t)(hash_table_t *ht);

typedef struct hash_table_entry_t {
    ht_key_value_t pair;            // 键值对
    hash_table_collision_entry_t *entry;    // 冲突链表入口
} hash_table_entry_t;

typedef struct hash_table_t {
    char *desc;
    size_t cur_size;            // 当前哈希表的总数据size
    size_t valid_size;          // 当前哈希表的有效size
    hash_table_entry_t *map;    // 当前哈希表映射

    // methods
    struct {
        hash_table_put_t *put;
        hash_table_get_t *get;
        hash_table_remove_t *remove;
        hash_table_rehash_t *rehash;
        hash_table_clear_t *clear;
    };
} hash_table_t;

hash_table_t *hash_table_create(char *desc, size_t pre_size);
void hash_table_destroy(hash_table_t *ht);


void hash_test ();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //CODEWAR_KATA_C_HASH_TABLE_H

/**
  ******************************************************************************
  * @file           : hash_table.h
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
typedef chain_node_t hash_table_key_value_t;

typedef struct hash_table_entry_t {
    hash_table_key_value_t pair;            // 键值对
    hash_table_collision_entry_t *entry;    // 冲突链表入口
} hash_table_entry_t;

typedef struct hash_table_t {
    char *desc;
    size_t cur_size;            // 当前哈希表的总数据size
    size_t valid_size;          // 当前哈希表的有效size
    hash_table_entry_t *map;    // 当前哈希表映射
} hash_table_t;

hash_table_t *hash_table(char *desc, size_t pre_size);
void hash_table_free(hash_table_t *ht);
int hash_table_put(hash_table_t *ht, char *key, void *value);
hash_table_key_value_t *hash_table_get(hash_table_t *ht, char *key);
void hash_table_remove(hash_table_t *ht, char *key);
void hash_table_rehash(hash_table_t *ht);
void hash_table_clear(hash_table_t *ht);

void hash_test ();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //CODEWAR_KATA_C_HASH_TABLE_H

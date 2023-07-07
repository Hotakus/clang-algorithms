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
#include "../../typedefs.h"

#define HASH_TEST 1

// 最大冲突比
#define HASH_TABLE_COLLISION_MAX_RADIO (0.375f)
// 最高性能倍数，大约为最大冲突比的10倍，过高或过低会导致平均性能下降，数量级越高越明显
#define HASH_TABLE_HIGHEST_PERFORMANCE_MULTIPLE (HASH_TABLE_COLLISION_MAX_RADIO * 10)
// 最大可接受负载因子，默认为1，若当前负载因子大于等于1，则进行再散列
#define HASH_TABLE_REHASH_FACTOR (1)

#ifdef __cplusplus
extern "C" {
#endif

typedef chain_t hash_table_collision_entry_t;
typedef chain_node_t ht_key_value_t;

/* Methods typedef -- Begin */
typedef struct hash_table_t hash_table_t;
typedef struct hash_table_map_elem_t hash_table_map_elem_t;
typedef enum ht_rehash_method_t ht_rehash_method_t;

typedef void (hash_table_limit_t)(hash_table_t *ht, size_t limit_size);
typedef int (hash_table_put_t)(hash_table_t *ht, const char *key, void *value);
typedef ht_key_value_t *(hash_table_get_t)(hash_table_t *ht, char *key);
typedef void (hash_table_remove_t)(hash_table_t *ht, char *key);
typedef void (hash_table_rehash_t)(hash_table_t *ht, size_t new_size);
typedef void (hash_table_clear_t)(hash_table_t *ht);
typedef void (hash_table_poll_t)(hash_table_t *ht);
/* Set and Get -- Begin */
typedef void (hash_table_set_ar_t)(hash_table_t *ht, bool ar);
typedef bool (hash_table_get_ar_t)(hash_table_t *ht);
typedef void (hash_table_set_rehash_method_t)(hash_table_t *ht, ht_rehash_method_t method);
/* Set and Get --  End */
/* Methods typedef --  End */

/* Hash table typedef -- Begin */
typedef enum ht_rehash_method_t {
    HASH_TABLE_REHASH_COLLISION = 0,
    HASH_TABLE_REHASH_LOAD_FACTOR,
} ht_rehash_method_t;

typedef struct hash_table_map_elem_t {
    ht_key_value_t pair;                    // 键值对
    hash_table_collision_entry_t *entry;    // 冲突链表入口
} hash_table_map_elem_t;

typedef struct hash_table_t {
    /* 公共变量 */
    char *desc;
    size_t cur_size;            // 当前哈希表的总数据size
    size_t valid_size;          // 当前哈希表的有效size
    size_t collision_cnt;       // 当前哈希表冲突数量

    /* 公共 methods */
    struct {
        hash_table_put_t *put;
        hash_table_get_t *get;
        hash_table_remove_t *remove;
        hash_table_rehash_t *rehash;
        hash_table_poll_t *poll;

        /* Set method */
        hash_table_set_ar_t *set_auto_rehash;    // set auto rehash
        hash_table_set_rehash_method_t *set_rehash_method; // set rehash method

        /* Get method */
        hash_table_get_ar_t *get_auto_rehash;    // get auto rehash
    };

    // 私有变量结构体, 程序调用，别修改
    private *pri;
} hash_table_t;
/* Hash table typedef --  End */

// 对外暴露的方法
hash_table_t *hash_table_create(char *desc, size_t pre_size);
void hash_table_destroy(hash_table_t *ht);

#if HASH_TEST == 1
void hash_test (int tn);
void hash_example();
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif  //CODEWAR_KATA_C_HASH_TABLE_H

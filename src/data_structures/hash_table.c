/**
  ******************************************************************************
  * @file           : hash_table_create.c
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/7/2
  ******************************************************************************
  */

#include <stdio.h>
#include "hash_table.h"

#if HASH_TEST == 1
#include <sys/time.h>
#endif

static void hash_table_limit(hash_table_t *ht, size_t limit_size);
static int hash_table_put(hash_table_t *ht, const char *key, void *value);
static ht_key_value_t *hash_table_get(hash_table_t *ht, char *key);
static void hash_table_remove(hash_table_t *ht, char *key);
static void hash_table_rehash(hash_table_t *ht, size_t new_size);
static void hash_table_clear(hash_table_t *ht);

static void hash_table_set_ar(hash_table_t *ht, bool ar);
static bool hash_table_get_ar(hash_table_t *ht);

// 私有变量结构体
struct private {
    hash_table_entry_t *map;    // 当前哈希表映射
    bool auto_rehash;           // 是否自动再散列，默认为 false
};


/**
 * 创建哈希表
 * @param desc 哈希表描述，可为空
 * @param pre_size 预分配size
 * @return 哈希表结构体
 */
hash_table_t *hash_table_create(char *desc, size_t pre_size) {
    hash_table_t *ht = (hash_table_t *) calloc(1, sizeof(hash_table_t));
    ht->cur_size = 0;
    ht->valid_size = 0;
    ht->collision_cnt = 0;
    ht->desc = desc;

    // 若 pre size 不为0，则分配指定长度的map
    if (!pre_size) {
        free(ht);
        ht = NULL;
        return ht;
    }

    ht->valid_size = pre_size;
    ht->pri = calloc(1, sizeof(private));
    ht->pri->map = (hash_table_entry_t *) calloc(ht->valid_size, sizeof(hash_table_entry_t));
    ht->pri->auto_rehash = false;

    // default method for hash table
    ht->limit = hash_table_limit;
    ht->put = hash_table_put;
    ht->get = hash_table_get;
    ht->remove = hash_table_remove;
    ht->rehash = hash_table_rehash;
    ht->clear = hash_table_clear;

    ht->set_ar = hash_table_set_ar;
    ht->get_ar = hash_table_get_ar;

    return ht;
}


/**
 * 清空哈希表
 * @param ht 要操作的哈希表
 */
void hash_table_clear(hash_table_t *ht) {
    if (ht->pri->map) {
        for (int i = 0; i < ht->valid_size; ++i) {
            if (ht->pri->map[i].entry) {
                chain_destroy(ht->pri->map[i].entry);
                ht->pri->map[i].entry = NULL;
            }
            ht->pri->map[i].pair.name = NULL;
            ht->pri->map[i].pair.data = NULL;
        }
        free(ht->pri->map);
    }

    ht->valid_size = 0;
    ht->cur_size = 0;
    ht->collision_cnt = 0;
}


/**
 * 销毁哈希表
 * @param ht 要销毁的哈希表
 */
void hash_table_destroy(hash_table_t *ht) {
    hash_table_clear(ht);
    if (ht->pri) free(ht->pri);
    free(ht);
}


/**
 *
 * @param ht
 * @param limit_size
 */
void hash_table_limit(hash_table_t *ht, size_t limit_size) {
    if (ht->valid_size < limit_size) {
        hash_table_rehash(ht, limit_size);
    }
}


/**
 * 哈希表Put
 * @param ht 要操作的哈希表
 * @param key 键
 * @param value 值
 * @return 哈希map索引
 */
int hash_table_put(hash_table_t *ht, const char *key, void *value) {

    // 若冲突总数值占有效空间数值的比例大于允许比例，则进行再散列
    if (ht->pri->auto_rehash) {
        float ratio = (float)ht->collision_cnt / (float)ht->valid_size;
        if (ratio > HASH_TABLE_COLLISION_MAX_RADIO) {
#if HASH_TEST == 1
            printf("1 rehash %zd (%zd) %f\n", ht->valid_size, ht->collision_cnt, ratio);
#endif
            hash_table_rehash(ht, (int)((float)ht->valid_size * HASH_TABLE_HIGHEST_PERFORMANCE_MULTIPLE));
#if HASH_TEST == 1
            printf("2 rehash %zd (%zd) %f\n", ht->valid_size, ht->collision_cnt, (float)ht->collision_cnt / (float)ht->valid_size);
#endif
        }
    }

    // calculate the hash code.
    int _hash_code = hash_code_fnv1a(key);
    int index = hash_limit(_hash_code, (int) ht->valid_size - 1);

    // determine whether entry was occupied.
    if (ht->pri->map[index].pair.name == NULL) {
        ht->pri->map[index].pair.name = key;
        ht->pri->map[index].pair.data = value;
        ht->cur_size += 1;
    } else {
        int res = BA_STRCMP(ht->pri->map[index].pair.name, key);
        if (res == 0) ht->pri->map[index].pair.data = value;
        else {
            // collision
            if (ht->pri->map[index].entry == NULL)
                ht->pri->map[index].entry = chain_create(NULL);
            hash_table_collision_entry_t *entry = ht->pri->map[index].entry;

            // find the collision chain
            ht_key_value_t *_find_kv = entry->find_node(entry, key, true);
            if (_find_kv) _find_kv->data = value;
            else {
                ht_key_value_t *pair = entry->node_new(key, value);
                entry->append(entry, pair);
                ht->collision_cnt += 1;
                ht->cur_size += 1;
            }
        }
    }

    return index;
}


/**
 * 哈希表Get键值对
 * @param ht 要操作的哈希表
 * @param key 要Get的key
 * @return 键值对
 */
ht_key_value_t *hash_table_get(hash_table_t *ht, char *key) {
    if (!key) return NULL;
    int _hash_code = hash_code_fnv1a(key);
    int index = hash_limit(_hash_code, (int) ht->valid_size - 1);

    if (ht->pri->map[index].pair.name == NULL) {
        hash_table_collision_entry_t *entry = ht->pri->map[index].entry;
        return entry ? entry->find_node(entry, key, true) : NULL;
    } else {
        int res = BA_STRCMP(ht->pri->map[index].pair.name, key);
        if (res == 0)
            return &ht->pri->map[index].pair;
        else {
            hash_table_collision_entry_t *entry = ht->pri->map[index].entry;
            return entry ? entry->find_node(entry, key, true) : NULL;
        }
    }
}


/**
 * 哈希表清指定键值对
 * @param ht 要操作的哈希表
 * @param key 要清除的键
 */
void hash_table_remove(hash_table_t *ht, char *key) {

    if (!ht) {
        return;
    }

    if (!key) {
        return;
    }

    int _hash_code = hash_code_fnv1a(key);
    int index = hash_limit(_hash_code, (int) ht->valid_size - 1);

    if (ht->pri->map[index].pair.name == NULL) {
        hash_table_collision_entry_t *entry = ht->pri->map[index].entry;
        if (!entry) return;
        entry->rm_node(entry, key, NULL);
    } else {
        int res = BA_STRCMP(ht->pri->map[index].pair.name, key);
        if (res == 0)
            ht->pri->map[index].pair.name = NULL;
        else {
            hash_table_collision_entry_t *entry = ht->pri->map[index].entry;
            if (!entry) return;
            entry->rm_node(entry, key, NULL);
            ht->collision_cnt -= 1;
        }
    }
    ht->cur_size -= 1;
}


/**
 * 哈希表再散列
 * @param ht 要操作的哈希表
 * @param new_size 哈希表新size
 */
void hash_table_rehash(hash_table_t *ht, size_t new_size) {
    if (!ht) {
        return;
    }

    // 数据暂存链表
    hash_table_collision_entry_t *temp_entry = chain_create("temp_entry");

    // 遍历哈希表，将键值对暂存入temp_entry
    for (size_t i = 0; i < ht->valid_size; ++i) {
        hash_table_collision_entry_t *entry = ht->pri->map[i].entry;

        if (ht->pri->map[i].pair.name) {
            ht_key_value_t *kv = temp_entry->node_new(ht->pri->map[i].pair.name, ht->pri->map[i].pair.data);
            temp_entry->append(temp_entry, kv);
        }

        // 遍历冲突链表
        if (entry) {
            ht_key_value_t *probe = entry->head->next_node;
            while (probe != ht->pri->map[i].entry->tail) {
                ht_key_value_t *_kv = entry->node_new(probe->name, probe->data);
                temp_entry->append(temp_entry, _kv);
                probe = probe->next_node;
            }
        }
    }

    // 再散列
    if (temp_entry->length == ht->cur_size) {
#if HASH_TEST == 1
        printf("!!!Rehash!!! -- May be time-consuming...\n");
#endif
        hash_table_clear(ht);
        ht->valid_size = new_size;
        ht->pri->map = (hash_table_entry_t *) calloc(ht->valid_size, sizeof(hash_table_entry_t));
        ht_key_value_t *probe = temp_entry->head->next_node;
        while (probe != temp_entry->tail) {
            ht->put(ht, probe->name, probe->data);
            probe = probe->next_node;
        }
    } else {
#if HASH_TEST == 1
        printf("%s verify error. (ht:%zu -- t:%zu)\n", __FUNCTION__, ht->cur_size, temp_entry->length);
#endif
    }

    chain_destroy(temp_entry);
}


void hash_table_set_ar(hash_table_t *ht, bool ar) {
    ht->pri->auto_rehash = ar;
}


bool hash_table_get_ar(hash_table_t *ht) {
    return ht->pri->auto_rehash;
}


#if HASH_TEST == 1
void hash_test(int tn) {

    int a = 996;
    int b = 114514;
    struct timeval begin, end;
    long long int dif_sec = 0;
    long long int dif_usec = 0;
    ssize_t res = 0;
    int test_nums = tn;
    ssize_t total = 0;

    printf("Number of tests: %d\n", test_nums);
    printf("Initializing...\n");
    srand(time(NULL));

    // Malloc test
    char **keys = calloc(test_nums, sizeof(char *));
    for (int i = 0; i < test_nums; ++i) {
        keys[i] = calloc(10, sizeof(char));
        sprintf(keys[i], "%s", rand_string(10));
    }

    // create test
    gettimeofday(&begin, NULL);
    hash_table_t *ht = hash_table_create("hash_table1", (int)((float)test_nums * HASH_TABLE_HIGHEST_PERFORMANCE_MULTIPLE));
    ht->set_ar(ht, true);
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Create    elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

    // Put test
    gettimeofday(&begin, NULL);
    for (int i = 0; i < test_nums; ++i) {
        ht->put(ht, keys[i], &a);
    }
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Put       elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

    // collision chain max length
    int max = 0;
    gettimeofday(&begin, NULL);
    for (int i = 0; i < test_nums; ++i) {
        if (ht->pri->map[i].entry)
            max = MAX(ht->pri->map[i].entry->length, max);
    }
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Max       collision chain length: %d\n", max);

    // single get test
    int rand_index = rand() % test_nums;
    ht->put(ht, keys[rand_index], &b);
    gettimeofday(&begin, NULL);
    ht_key_value_t *kv = ht->get(ht, keys[rand_index]);
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("SingleGet elapsed time: %lld secs, %lld ms, %lld us (%s : %d - %s)\n",
           (res / 1000000), (res / 1000), res,
           kv->name, *(int*)kv->data,
           IS_TRUE(*(int*)kv->data == b));


    // get test
    gettimeofday(&begin, NULL);
    for (int i = 0; i < test_nums; ++i) {
        ht_key_value_t *pair = ht->get(ht, keys[i]);
    }
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Get       elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

    // rehash test
//    gettimeofday(&begin, NULL);
//    printf("\nRehash start--------\n");
    printf("Before collision count: %zd, valid size: %zd\n", ht->collision_cnt, ht->valid_size);
//    hash_table_rehash(ht, test_nums * 2);
//    printf("After  collision count: %zd, valid size: %zd\n", ht->collision_cnt, ht->valid_size);
//    printf("Rehash  end --------\n\n");
//    gettimeofday(&end, NULL);
//    dif_sec = end.tv_sec - begin.tv_sec;
//    dif_usec = end.tv_usec - begin.tv_usec;
//    res = dif_sec * 1000000 + dif_usec;
//    total += res;
//    printf("Rehash    elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);


    // destroy test
    gettimeofday(&begin, NULL);
    hash_table_destroy(ht);
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Destro    elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

    // Free test
    gettimeofday(&begin, NULL);
    for (int i = 0; i < test_nums; ++i) {
        free(keys[i]);
    }
    free(keys);
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Free      elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

    printf("Total     elapsed time: %lld secs, %lld ms, %lld us\n", (total / 1000000), (total / 1000), total);
}
#endif

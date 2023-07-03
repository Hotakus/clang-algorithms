/**
  ******************************************************************************
  * @file           : hash_table_create.c
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/7/2
  ******************************************************************************
  */

#include <stdio.h>
#include <sys/time.h>
#include "hash_table.h"
#include "./include/chain.h"


static int hash_table_put(hash_table_t *ht, char *key, void *value);
static ht_key_value_t *hash_table_get(hash_table_t *ht, char *key);
static void hash_table_remove(hash_table_t *ht, char *key);
static void hash_table_rehash(hash_table_t *ht);
static void hash_table_clear(hash_table_t *ht);


hash_table_t *hash_table_create(char *desc, size_t pre_size) {
    hash_table_t *ht = (hash_table_t *) calloc(1, sizeof(hash_table_t));
    ht->cur_size = 0;
    ht->valid_size = 0;
    ht->desc = desc;

    // 若 pre size 不为0，则分配指定长度的map
    if (pre_size) {
        ht->valid_size = pre_size + 1;
        ht->map = (hash_table_entry_t *) calloc(ht->valid_size, sizeof(hash_table_entry_t));
    }

    // default method for hash table
    ht->put = hash_table_put;
    ht->get = hash_table_get;
    ht->remove = hash_table_remove;
    ht->rehash = hash_table_rehash;
    ht->clear = hash_table_clear;

    return ht;
}

void hash_table_destroy(hash_table_t *ht) {
    if (ht->map) {
        for (int i = 0; i < ht->valid_size; ++i)
            if (ht->map[i].entry)
                chain_destroy(ht->map[i].entry);
        free(ht->map);
    }
    free(ht);
}

int hash_table_put(hash_table_t *ht, char *key, void *value) {
    if (!ht) {
        return -1;
    }

    if (!key) {
        return -1;
    }

    // calculate the hash code.
    int _hash_code = hash_code_fnv1a(key);
    int index = hash_limit(_hash_code, (int) ht->valid_size - 1);

    // determine whether entry was occupied.
    if (ht->map[index].pair.name == NULL) {
        ht->map[index].pair.name = key;
        ht->map[index].pair.data = value;
    } else if (BA_STRCMP(ht->map[index].pair.name, key) != 0) {
        // collision
        if (ht->map[index].entry == NULL)
            ht->map[index].entry = chain_create(NULL);
        hash_table_collision_entry_t *entry = ht->map[index].entry;

        // find the collision chain
        ht_key_value_t *_find_kv = entry->find_node(entry, key, true);
        if (_find_kv) {
            _find_kv->data = value;
            return index;
        }
        ht_key_value_t *pair = entry->node_new(entry, key);
        pair->data = value;
        entry->append(entry, pair);
    } else if (BA_STRCMP(ht->map[index].pair.name, key) == 0)
        ht->map[index].pair.data = value;

    ht->cur_size += 1;

    return index;
}


ht_key_value_t *hash_table_get(hash_table_t *ht, char *key) {
    if (!key) return NULL;
    int _hash_code = hash_code_fnv1a(key);
    int index = hash_limit(_hash_code, (int) ht->valid_size - 1);

    if (ht->map[index].pair.name == NULL) {
        hash_table_collision_entry_t *entry = ht->map[index].entry;
        return entry ? entry->find_node(entry, key, true) : NULL;
    } else {
        int res = BA_STRCMP(ht->map[index].pair.name, key);
        if (res == 0)
            return &ht->map[index].pair;
        else {
            hash_table_collision_entry_t *entry = ht->map[index].entry;
            return entry ? entry->find_node(entry, key, true) : NULL;
        }
    }
}


void hash_table_remove(hash_table_t *ht, char *key) {

    if (!ht) {
        return;
    }

    if (!key) {
        return;
    }

    int _hash_code = hash_code_fnv1a(key);
    int index = hash_limit(_hash_code, (int) ht->valid_size - 1);

    if (ht->map[index].pair.name == NULL) {
        hash_table_collision_entry_t *entry = ht->map[index].entry;
        if (!entry) return;
        entry->rm_node(entry, key, NULL);
    } else {
        int res = BA_STRCMP(ht->map[index].pair.name, key);
        if (res == 0)
            ht->map[index].pair.name = NULL;
        else {
            hash_table_collision_entry_t *entry = ht->map[index].entry;
            if (!entry) return;
            entry->rm_node(entry, key, NULL);
        }
    }
    ht->cur_size -= 1;
}

void hash_table_rehash(hash_table_t *ht) {

}

void hash_table_clear(hash_table_t *ht) {

}


void hash_test() {
    int a = 996;
    int b = 114514;
    struct timeval begin, end;
    long long int dif_sec = 0;
    long long int dif_usec = 0;
    ssize_t res = 0;
    int test_nums = 10000000;
    ssize_t total = 0;

    printf("Testing: %d\n", test_nums);

    // create test
    gettimeofday(&begin, NULL);
    hash_table_t *ht = hash_table_create("hash_table1", test_nums * 2);
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Create    elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

    // Malloc test
    gettimeofday(&begin, NULL);
    srand(time(NULL));
    char **keys = calloc(test_nums, sizeof(char *));
    for (int i = 0; i < test_nums; ++i) {
        keys[i] = calloc(10, sizeof(char));
        sprintf(keys[i], "%s", rand_string(10));
    }
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Rand keys elapsed time: %lld secs, %lld ms, %lld us\n", (res / 1000000), (res / 1000), res);

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
        if (ht->map[i].entry)
            max = MAX(ht->map[i].entry->length, max);
    }
    gettimeofday(&end, NULL);
    dif_sec = end.tv_sec - begin.tv_sec;
    dif_usec = end.tv_usec - begin.tv_usec;
    res = dif_sec * 1000000 + dif_usec;
    total += res;
    printf("Max       collision chain length: %d\n", max);

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


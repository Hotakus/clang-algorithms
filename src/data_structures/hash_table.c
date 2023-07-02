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
}

void hash_table_rehash(hash_table_t *ht) {

}

void hash_table_clear(hash_table_t *ht) {

}


void hash_test() {
    int a = 114514;
    int b = 1145142;
    int c = 904;
    hash_table_t *ht = hash_table_create("test_hash", 1);

    ht->put(ht, "hello1", &a);
    ht->put(ht, "hello2", &b);
    ht->put(ht, "hello3", &c);
    ht->put(ht, "hello4", &c);

    ht_key_value_t *pair1 = ht->get(ht, "hello1");
    ht_key_value_t *pair2 = ht->get(ht, "hello2");
    ht_key_value_t *pair3 = ht->get(ht, "hello3");
    ht_key_value_t *pair4 = ht->get(ht, "hello4");


    printf("%s: %d\n", pair1->name, *(int *) pair1->data);
    printf("%s: %d\n", pair2->name, *(int *) pair2->data);
    printf("%s: %d\n", pair3->name, *(int *) pair3->data);
    printf("%s: %d\n", pair4->name, *(int *) pair4->data);

    hash_table_remove(ht, "hello4");

    ht->map[0].entry->poll(ht->map[0].entry, true);
    ht->map[1].entry->poll(ht->map[1].entry, true);

    hash_table_destroy(ht);
}


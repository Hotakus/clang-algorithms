#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include "find_odd_int.h"

typedef struct {
    size_t key;
    size_t value;
} kv_dict_t;

int find_odd (size_t length, const int array[])
{
    int result = 0;
    int val;
    int val_type = 1;

    kv_dict_t* kv = (kv_dict_t*)malloc(sizeof(kv_dict_t) * val_type);

    for (int i = 0; i < length; i++) {

    }

    printf("%d\n", kv->key);
    printf("%d\n", kv->value);

    free(kv);
    return result;
}

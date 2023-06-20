#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include "include/find_odd_int.h"

int find_odd (size_t length, const int *array)
{
    int res = array[0];
    for (int i = 1; i < length; ++i) {
        res ^= array[i];
    }
    return res;
}

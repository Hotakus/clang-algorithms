#include "include/sort.h"
#include "include/utilities.h"


int *bubble_sort_int(int *src, uint64_t len, bool is_descent) {
    if (src == NULL || len == 0) return NULL;
    for (uint64_t i = 0; i < len - 1; ++i) {
        for (int k = 0; k < len - i - 1; ++k) {
            if (is_descent ? (src[k] < src[k + 1]) : src[k] > src[k + 1]) {
                int t = src[k];
                src[k] = src[k + 1];
                src[k + 1] = t;
            }
        }
    }
    return NULL;
}

char *bubble_sort_char(char *src, bool is_descent) {
    uint64_t len = BA_STRLEN(src);
    if (src == NULL || len == 0) return NULL;
    for (uint64_t i = 0; i < len - 1; ++i) {
        for (int k = 0; k < len - i - 1; ++k) {
            if (is_descent ? (src[k] < src[k + 1]) : src[k] > src[k + 1]) {
                char t = src[k];
                src[k] = src[k + 1];
                src[k + 1] = t;
            }
        }
    }
    return NULL;
}

char *bubble_sort_str_arr(char **src, bool is_descent) {

    return NULL;
}

void *bubble_sort_void(void *src, bool is_descent) {
    if (src == NULL) return NULL;
    return NULL;
}


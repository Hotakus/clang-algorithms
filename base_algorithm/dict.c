#include <malloc.h>
#include "include/dict.h"



dict_t* dict_create() {
    return (dict_t*)malloc(sizeof(dict_t));
}

void dict_destroy(dict_t *d) {
    if (d) free(d);
}

/**
 * Add a element to for a dict.
 * @param key dict's key
 * @param value dict's value
 */
void dict_add_element(const char *key, const void *value) {

}



/**
 * Finds the element by key
 * @param key
 */
void dict_find(const char *key) {

}

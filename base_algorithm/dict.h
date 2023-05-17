#ifndef CODEWAR_KATA_C_DICT_H
#define CODEWAR_KATA_C_DICT_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* key;
    void* value;
} dict_t;

dict_t* dict_create();
void dict_destroy(dict_t* d);
void dict_add_element(const char* key, const void* value);
void dict_find(const char* key);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_DICT_H

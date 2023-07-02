#ifndef CODEWAR_KATA_C_CONFIG_H
#define CODEWAR_KATA_C_CONFIG_H

/**
 * 1 : enable
 * 0 : disable
 */

#define DEBUG 0

// chain
#define USE_CHAIN_SEM 0
#define USE_CHAIN_MINI 0

// utilities
#define USE_CUSTOM_STR 1
#if USE_CUSTOM_STR == 0
#include <string.h>
#define BA_STRCMP(str1, str2)   strcmp(str1, str2)
#define BA_STRLEN(str)          strlen(str)
#define BA_STRCPY(dst, src)     strcpy(dst, src)
#define BA_STRCHR(ch, str)      strchr(ch, str)
#else
#include "algorithms/include/utilities.h"
#define BA_STRCMP(str1, str2)   str_cmp(str1, str2)
#define BA_STRLEN(str)          str_len(str)
#define BA_STRCPY(dst, src)     str_cpy(dst, src)
#define BA_STRCHR(ch, str)      str_chr(ch, str)
#endif

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_CONFIG_H

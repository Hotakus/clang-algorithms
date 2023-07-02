/**
  ******************************************************************************
  * @file           : hash.h
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/7/2
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_HASH_H
#define CODEWAR_KATA_C_HASH_H

#include <stdint.h>

#define OFFSET_BASIS_32     (0x811c9dc5)
#define FNV_PRIME_32        ((uint32_t)16777619)


#ifdef __cplusplus
extern "C" {
#endif

int hash_code_fnv1a(char *key);
int hash_downgrade(int code, int bits);
int hash_limit(int code, int max);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //CODEWAR_KATA_C_HASH_H

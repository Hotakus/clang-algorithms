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

#define HASH_CODE_BITS      32
#define OFFSET_BASIS_32     (0x811c9dc5)
#define FNV_PRIME_32        ((uint32_t)16777619)

#if HASH_CODE_BITS == 32
#define OFFSET_BASIS        (OFFSET_BASIS_32)
#define FNV_PRIME           (FNV_PRIME_32)
#endif

#ifdef __cplusplus
extern "C" {
#endif

int32_t hash_code_fnv1a(char *key);
int32_t hash_downgrade(int32_t code, int bits);
int32_t hash_limit(int32_t code, int max);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //CODEWAR_KATA_C_HASH_H

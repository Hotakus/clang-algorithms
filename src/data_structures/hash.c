/**
  ******************************************************************************
  * @file           : hash.c
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/7/2
  ******************************************************************************
  */

#include <math.h>
#include "./include/hash.h"
#include "../config.h"


/**
 * 使用FNV-1a算法, 将字符串转 hash code
 * @param key 要计算的字符串键值
 * @return hash code
 */
int hash_code_fnv1a(char *key) {
    int _hash_code = OFFSET_BASIS_32;
    for (int i = 0; i < BA_STRLEN(key); ++i) {
        _hash_code ^= key[i];
        _hash_code *= FNV_PRIME_32;
    }
    return _hash_code;
}

int hash_downgrade(int code, int bits) {
    return abs((code >> bits) ^ (code & ((1 << bits) - 1)));
}

/**
 * hash限值
 * @param code 要限定的hash code
 * @param max hash最大值
 * @return 限值后的hash code
 */
int hash_limit(int code, int max) {
    return abs(code % (max + 1));
}

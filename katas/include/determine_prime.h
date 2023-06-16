/**
  ******************************************************************************
  * @file      : determine_prime.h
  * @author    : Hotakus
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/16
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_DETERMINE_PRIME_H
#define CODEWAR_KATA_C_DETERMINE_PRIME_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


bool prime_determine(int num, bool opt);
bool prime_eratosthenes(int num);
bool prime_euler(int num);


/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_DETERMINE_PRIME_H

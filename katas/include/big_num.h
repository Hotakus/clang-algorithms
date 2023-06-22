/**
  ******************************************************************************
  * @file      : big_num.h
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/18
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_BIG_NUM_H
#define CODEWAR_KATA_C_BIG_NUM_H

#define BIG_NUM_MUL_USE_NORMAL      1
#define BIG_NUM_MUL_USE_KARATSUBA   0
#define BIG_NUM_MUL_USE_FNTT        0

#ifdef __cplusplus
extern "C" {
#endif

char *num_trailing_zeros(char *num);

char *big_num_add(const char *num1, const char *num2);
char *big_num_multiply(const char *num1, const char *num2);
void big_num_free(char *num);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_BIG_NUM_H

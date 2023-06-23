/**
  ******************************************************************************
  * @file      : num_english.h
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/17
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_NUM_ENGLISH_H
#define CODEWAR_KATA_C_NUM_ENGLISH_H

#ifdef __cplusplus
extern "C" {
#endif


char *num2English(long long int num);
void num2English_free(char *src, int num);

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_NUM_ENGLISH_H

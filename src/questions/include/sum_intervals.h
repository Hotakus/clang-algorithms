/**
  ******************************************************************************
  * @file      : sum_intervals.h
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/25
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_SUM_INTERVALS_H
#define CODEWAR_KATA_C_SUM_INTERVALS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct interval {
    int first;
    int second;
} interval_t;

int sum_intervals(const interval_t *v, size_t n);

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_SUM_INTERVALS_H

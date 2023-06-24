/**
  ******************************************************************************
  * @file      : h_math.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/24
  ******************************************************************************
  */

#include "./include/h_math.h"

float h_fast_sqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int *) &x;
    
    i = 0x5f375a86 - (i >> 1);
    x = *(float *) &i;
    x = x * (1.5f - xhalf * x * x);
    x = x * (1.5f - xhalf * x * x);
    x = x * (1.5f - xhalf * x * x);

    return 1 / x;
}

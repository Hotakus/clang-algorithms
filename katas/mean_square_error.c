/**
  ******************************************************************************
  * @file      : mean_square_error.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/20
  ******************************************************************************
  */

/**
 * accepts two integer arrays of equal length
 * compares the value each member in one array to the corresponding member in the other
 * squares the absolute value difference between those two values
 * and returns the average of those squared absolute value difference between each member pair.
 */

#include <math.h>
#include "include/mean_square_error.h"

double mean_square_error(size_t len, const int *src1, const int *src2) {
    double ret = 0;
    for (size_t i = 0; i < len; ++i)
        ret += pow(src1[i] - src2[i], 2);
    return ret / ((double) len);
}

/**
  ******************************************************************************
  * @file      : sum_intervals.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/25
  ******************************************************************************
  */

#include "sum_intervals.h"
#include <stdlib.h>


void bubble_sort_interval(interval_t *src, int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int k = 0; k < len - i - 1; ++k) {
            if (src[k].first > src[k + 1].first) {
                interval_t t = src[k];
                src[k] = src[k + 1];
                src[k + 1] = t;
            }
        }
    }
}


int sum_intervals(const interval_t *v, size_t n) {
    int sum = 0;
    bubble_sort_interval(v, n);
    int sec_max = v[0].second;
    sum += v[0].second - v[0].first;
    for (size_t i = 0; i < n; ++i) {
        if (v[i].first < sec_max) { // if cross
            if (v[i].second > sec_max)
                sum += v[i].second - sec_max;
        } else
            sum += v[i].second - v[i].first;

        if (v[i].second > sec_max) sec_max = v[i].second;
    }
    return sum;
}

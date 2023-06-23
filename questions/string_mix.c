/**
  ******************************************************************************
  * @file      : string_mix.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/23
  ******************************************************************************
  */

#include <stdlib.h>
#include <stdio.h>
#include "../basic_algorithm/config.h"
#include "include/string_mix.h"

char *string_mix(const char *s1, const char *s2) {
    unsigned char flag_list[] = "12=";
    unsigned char alpha1[128] = {0};
    unsigned char alpha2[128] = {0};
    unsigned char alpha_res[128] = {0};
    unsigned char alpha_flag[128] = {0};
    const char *p1 = s1;
    const char *p2 = s2;

    while (*p1 != '\0' || *p2 != '\0') {
        if (*p1 != '\0') alpha1[*p1++] += 1;
        if (*p2 != '\0') alpha2[*p2++] += 1;
    }

    unsigned int max = 0;
    unsigned short cnt = 0;
    unsigned short wn = 0;
    for (unsigned char i = 'a'; i <= 'z'; ++i) {
        if (alpha1[i] <= 1 && alpha2[i] <= 1)
            continue;
        if (alpha1[i] == alpha2[i]) {
            alpha_flag[i] = flag_list[2];
            alpha_res[i] = alpha1[i];
        } else if (alpha1[i] > alpha2[i]) {
            alpha_flag[i] = flag_list[0];
            alpha_res[i] = alpha1[i];
        } else if (alpha1[i] < alpha2[i]) {
            alpha_flag[i] = flag_list[1];
            alpha_res[i] = alpha2[i];
        }
        cnt += 1;
        wn += alpha_res[i];
        max = MAX(max, alpha_res[i]);
    }

    // (cnt - 1) : count of '/';    (cnt * 2) : count of '=:';
    int allocation_cnt = wn + (cnt - 1) + (cnt * 2) + 1;
    char *res = (char *) calloc(allocation_cnt, sizeof(char));
    char *pr = res;
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < ARRAY_SIZE(flag_list); ++j) {
            for (unsigned char k = 'a'; k <= 'z'; ++k) {
                if ((alpha_res[k] == 0) || (alpha_res[k] != max)) continue;
                if (alpha_flag[k] == flag_list[j]) {
                    sprintf(pr, "/%c:",alpha_flag[k]); pr += 3;
                    for (int m = 0; m < alpha_res[k]; ++m) *pr++ = k;
                }
            }
        }
        max -= 1;
    }
    *pr = '\0';
    BA_STRCPY(res, &res[1]);
    return res;
}

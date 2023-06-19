/**
  ******************************************************************************
  * @file      : big_num.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/18
  ******************************************************************************
  */

#include <stdlib.h>
#include "big_num.h"
#include "../base_algorithm/ba.h"

/**
 * 1. determine digits who is bigger.
 * 2. align digits and allocate a array.
 * 3. add digits one by one.
 * 4. carrying digits if it bigger than 10.
 * 5. if digits len is bigger than old one, then reallocate array.
 */

/**
 * 大数相加
 * @param a 大数a
 * @param b 大数b
 * @return 结果
 */
char *big_num_add(const char *a, const char *b) {

    unsigned char len_a = BA_STRLEN(a);
    unsigned char len_b = BA_STRLEN(b);
    unsigned char len_max = MAX(len_a, len_b);

    char *num_buf = (char *) calloc(len_max + 1 + 1, sizeof(char));
    num_buf[len_max + 1] = '\0';

    int carry = 0;
    int lm = len_max;
    for (int k = 0; k < len_max; ++k) {
        int digit = carry;
        if ((len_a - k - 1) >= 0)
            digit += a[len_a - k - 1] - '0';
        if ((len_b - k - 1) >= 0)
            digit += b[len_b - k - 1] - '0';

        num_buf[lm - k] = (char) ((digit % 10) + '0');
        carry = digit / 10;
    }

    if (carry) {
        num_buf[0] = carry + '0';
    } else {
        char *tmp = (char *) calloc(len_max + 1, sizeof(char));
        char *nb = num_buf;
        BA_STRCPY(tmp, &num_buf[1]);
        num_buf = tmp;
        free(nb);
    }

    return num_buf;
}

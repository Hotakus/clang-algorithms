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
#include "../basic_algorithm//ba.h"


/**
 * 大数相加
 * @param a 大数a
 * @param b 大数b
 * @return 结果
 */
char *big_num_add(const char *num1, const char *num2) {
    /**
     * 1. determine digits who is bigger.
     * 2. align digits and allocate a array.
     * 3. add digits one by one.
     * 4. carrying digits if it bigger than 10.
     * 5. if digits len is bigger than old one, then reallocate array.
     */

    // 无值赋零
    if (num1[0] == NULL) num1 = "0";
    else if (num2[0] == NULL) num2 = "0";

    num1 = num_trailing_zeros(num1);
    num2 = num_trailing_zeros(num2);

    // TODO: 改进
    unsigned char len_a = BA_STRLEN(num1);
    unsigned char len_b = BA_STRLEN(num2);
    unsigned char len_max = MAX(len_a, len_b);

    char *num_buf = (char *) calloc(len_max + 1 + 1, sizeof(char));
    num_buf[len_max + 1] = '\0';

    int carry = 0;
    int lm = len_max;
    for (int k = 0; k < len_max; ++k) {
        int digit = carry;
        if ((len_a - k - 1) >= 0)
            digit += num1[len_a - k - 1] - '0';
        if ((len_b - k - 1) >= 0)
            digit += num2[len_b - k - 1] - '0';

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


// TODO: 实现更多大数乘方法
char *big_num_multiply(const char *num1, const char *num2) {

    // 无值赋零
    if (num1[0] == NULL) num1 = "0";
    else if (num2[0] == NULL) num2 = "0";

    num1 = num_trailing_zeros(num1);
    num2 = num_trailing_zeros(num2);

    if (num1[0] == NULL || num2[0] == NULL) {
        char *tmp = calloc(1, 1);
        tmp[0] = '0';
        return tmp;
    }

    unsigned short len_1 = BA_STRLEN(num1);
    unsigned short len_2 = BA_STRLEN(num2);
    unsigned int   len = len_1 + len_2;

    char *digits = (char *) calloc(len + 1, sizeof(char));

    for (int i = len_1 - 1; i >= 0; --i) {
        unsigned char carry = 0;
        for (int k = len_2 - 1; k >= 0; --k) {
            unsigned char res = (num1[i] - '0') * (num2[k] - '0');
            carry = res / 10;
            digits[k + i + 1] += res % 10;
            if (carry)
                digits[k + i] += carry;
        }

        // 进位
        for (int k = len_2 - 1; k >= 0; --k) {
            if (digits[k + i + 1] == 0) continue;
            carry = digits[k + i + 1] / 10;
            digits[k + i + 1] = digits[k + i + 1] % 10;
            digits[k + i] += carry;
        }
    }

    // 转数字为字符并分拷贝到新空间
    for (int k = 0; (k < len); ++k)
        digits[k] += '0';
    if (digits[0] == '0') {
        char *tmp = calloc(len + 1, sizeof(char));
        BA_STRCPY(tmp, &digits[1]);
        free(digits);
        digits = tmp;
    }

    digits[len] = '\0';
    return digits;
}

void big_num_free(char *num) {
    if (num == NULL) {
#if DEBUG == 1
        printf("%s pointer is null\n", __FUNCTION__);
#endif
    }
}

/**
 * 去除数字字符串中的前置trailing的0
 * @param num
 * @return
 */
char *num_trailing_zeros(char *num) {
    while (*num++ == '0' && (num != '\0'));
    return --num;
}

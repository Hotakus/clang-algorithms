/**
  ******************************************************************************
  * @file      : num_english.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/17
  ******************************************************************************
  */

#include "../algorithms/ba.h"
#include <stddef.h>
#include <stdlib.h>
#include "num_english.h"

const static char *digits[] = {"zero", "one", "two", "three", "four",
                               "five", "six", "seven", "eight", "nine"};
const static char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen",
                              "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const static char *tens[] = {"", "", "twenty", "thirty", "forty",
                             "fifty", "sixty", "seventy", "eighty", "ninety"};

const static char *hundred = "hundred";

char *num2English(long long int num) {
    if (num >= 0 && num <= 9) {
        return (char *) digits[num];
    } else if (num >= 10 && num <= 19) {
        return (char *) teens[num - 10];
    } else if (num >= 20 && num <= 99) {
        int tens_digit = num / 10;
        int ones_digit = num % 10;
        if (ones_digit == 0) {
            return (char *) tens[tens_digit];
        } else {
            char *buf = (char *) calloc(BA_STRLEN(tens[tens_digit]) + BA_STRLEN(digits[ones_digit]) + 1, sizeof(char));
            sprintf(buf, "%s-%s", tens[tens_digit], digits[ones_digit]);
            return buf;
        }
    } else if (num >= 100 && num <= 999) {
        int hundreds_digit = num / 100;
        int remaining_num = num % 100;

        if (remaining_num == 0) {
            char *buf = (char *) calloc(BA_STRLEN(digits[hundreds_digit]) + BA_STRLEN(hundred) + 1, sizeof(char));
            sprintf(buf, "%s %s", digits[hundreds_digit], hundred);
            return buf;
        } else {
            char *r_buf = num2English(remaining_num);
            char *buf = (char *) calloc(BA_STRLEN(digits[hundreds_digit]) + BA_STRLEN(hundred) + BA_STRLEN(r_buf) + 7, sizeof(char));
            sprintf(buf, "%s %s and %s", digits[hundreds_digit], hundred, r_buf);
            num2English_free(r_buf, remaining_num);
            return buf;
        }
    }

    return NULL;
}

void num2English_free(char *src, int num) {
    if (num > 20 && (num % 10 != 0))
        free(src);
}




// Sort - one, three, two
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//
//#define BA_STRCMP(str1, str2)   strcmp(str1, str2)
//#define BA_STRLEN(str)          strlen(str)
//#define BA_STRCPY(dst, src)     strcpy(dst, src)
//
//char *digits[] = {"zero", "one", "two", "three", "four",
//                  "five", "six", "seven", "eight", "nine"};
//char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen",
//                 "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
//char *tens[] = {"", "", "twenty", "thirty", "forty",
//                "fifty", "sixty", "seventy", "eighty", "ninety"};
//char *hundred = "hundred";
//
//
//void num2English_free(char *src, int num) {
//    if (num > 20 && (num % 10 != 0))
//        free(src);
//}
//
//char *num2English(long long int num) {
//    if (num >= 0 && num <= 9) {
//        return (char *) digits[num];
//    } else if (num >= 10 && num <= 19) {
//        return (char *) teens[num - 10];
//    } else if (num >= 20 && num <= 99) {
//        int tens_digit = num / 10;
//        int ones_digit = num % 10;
//        if (ones_digit == 0) {
//            return (char *) tens[tens_digit];
//        } else {
//            char *buf = (char *) calloc(BA_STRLEN(tens[tens_digit]) + BA_STRLEN(digits[ones_digit]) + 5, sizeof(char));
//            sprintf(buf, "%s-%s", tens[tens_digit], digits[ones_digit]);
//            return buf;
//        }
//    } else if (num >= 100 && num <= 999) {
//        int hundreds_digit = num / 100;
//        int remaining_num = num % 100;
//
//        if (remaining_num == 0) {
//            char *buf = (char *) calloc(BA_STRLEN(digits[hundreds_digit]) + BA_STRLEN(hundred) + 5, sizeof(char));
//            sprintf(buf, "%s %s", digits[hundreds_digit], hundred);
//            return buf;
//        } else {
//            char *r_buf = num2English(remaining_num);
//            char *buf = (char *) calloc(BA_STRLEN(digits[hundreds_digit]) + BA_STRLEN(hundred) + BA_STRLEN(r_buf) + 8, sizeof(char));
//            sprintf(buf, "%s %s and %s", digits[hundreds_digit], hundred, r_buf);
//            num2English_free(r_buf, remaining_num);
//            return buf;
//        }
//    }
//
//    return NULL;
//}
//
//char *bubble_sort_str_arr(char **src, int *index, int len, bool is_descent) {
//    if (src == NULL || len == 0) return NULL;
//    for (int i = 0; i < len - 1; ++i) {
//        for (int k = 0; k < len - i - 1; ++k) {
//            if (is_descent ? (BA_STRCMP(src[k], src[k + 1]) < 0) : (BA_STRCMP(src[k], src[k + 1]) > 0)) {
//                char *t = src[k];
//                src[k] = src[k + 1];
//                src[k + 1] = t;
//
//                int t2 = index[k];
//                index[k] = index[k + 1];
//                index[k + 1] = t2;
//            }
//        }
//    }
//    return NULL;
//}
//
//int *sort(const int *array, int length)
//{
//    if (length == 0) return NULL;
//    char **num_str = (char **)calloc(length + 1, sizeof(char*));
//    int *res = (int *)calloc(length + 1, sizeof(int));
//
//    for (int i = 0; i < length; ++i) {
//        num_str[i] = num2English(array[i]);
//        res[i] = array[i];
//    }
//
//    bubble_sort_str_arr(num_str, res, length, false);
//
//    for (int i = 0; i < length; ++i)
//        num2English_free(num_str[i], res[i]);
//    return res;
//}

/**
  ******************************************************************************
  * @file      : determine_prime.c
  * @author    : Hotakus
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/16
  ******************************************************************************
  */

#include <math.h>
#include "determine_prime.h"


bool prime_determine(int num, bool opt) {
    if (num <= 1)
        return false;
    for (int i = 2; i <= (opt ? (int)sqrt(num) : (num >> 1)); ++i)
        if (num % i == 0)
            return false;
    return true;
}


bool prime_eratosthenes(int num) {
    return 0;
}


bool prime_euler(int num) {
    return 0;
}

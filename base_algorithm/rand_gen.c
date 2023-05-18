#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rand_gen.h"


#define DEBUG 0


ssize_t rand_gen(int digits) {
    ssize_t result = 0;
    char single_digit = 0;

    srand(time(NULL));
    for(int j = 0; j < digits; j++){
        single_digit = (char)(rand() % 10);
        result += single_digit * (ssize_t)pow(10, j);
    }

    return result;
}
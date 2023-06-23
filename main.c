#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include "main.h"


char *str1 = "pqmpgtzzfaqftdawjqiurwscy";
char *str2 = "fevbekrsaanbbsbrzwwbvfsdb";
char *ex = "2:bbbbbb/1:qqq/2:sss/1:pp/1:tt/1:zz/2:ee/2:rr/2:vv/=:aa/=:ff/=:ww";


static int tf1(int a, int b) {
    return a + b;
}

static int tf2(int a, int b) {
    return a * b;
}


typedef int (*test_func_t)(int a, int b);

typedef struct {
    test_func_t tf;
}test_struct_t;

int main() {
    long long int cost_time = run_time(COUNT_TIME_US, chain_test);
    run_time_show(&cost_time);
    return 0;
}
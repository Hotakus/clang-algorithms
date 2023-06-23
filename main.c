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

//    test_struct_t a;
//    a.tf = tf2;
//    printf("%d\n", a.tf(123,2));
//
//    char *res = string_mix(str1, str2);
//    printf("ex : %s\n", ex);
//    printf("ac : %s\n", res);
//    printf("%s\n", IS_TRUE(BA_STRCMP(res, ex) == 0));
//    free(res);

    chain_test();

    return 0;
}
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

int main() {
    char *res = string_mix(str1, str2);
    printf("ex : %s\n", ex);
    printf("ac : %s\n", res);
    printf("%s\n",IS_TRUE(BA_STRCMP(res, ex) == 0));
    free(res);
    return 0;
}
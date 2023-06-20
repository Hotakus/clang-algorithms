#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "main.h"
#include "katas/include/num_english.h"

char *str = "hello world asd x2 21 a !";



int main() {

    int a[] = {1,2,2,3,3,3,4,3,3,3,2,2,1};

    int res = find_odd(ARRAY_SIZE(a), a);
    printf("found odd number: %d\n", res);

    return 0;
}
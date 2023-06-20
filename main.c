#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "main.h"
#include "katas/include/num_english.h"

char *str = "hello world asd x2 21 a !";

char *range_conn(const int *args, int i) {

}

char *range_extraction(const int *args, size_t n)
{
    const int *pa = args;
    int *t = calloc(1, sizeof(char));

    for (int i = 1; i < n; ++i) {
        if ((args[i-1] + 1) != args[i]) {
            BA_STRCPY(t, range_conn(pa, i));
            pa += i;
        }

    }


    return NULL;
}

int main() {

    int a[] = {1,2,2,3,3,3,4,3,3,3,2,2,1};

    int res = find_odd(ARRAY_SIZE(a), a);
    printf("found odd number: %d\n", res);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "main.h"

void fun_test() {
    char *str1 = NULL;
    char *str2 = NULL;

    // lcs test
    printf("------------------ LCS Test (Begin) ------------------\n");
    str1 = "nothardlythefinaltest";
    str2 = "zzzfinallyzzz";
    lcs_t *res_lcs = lcs_solve(str1, str2);
    char *res = lcs_body(res_lcs);
    printf("%s\n", res);
    printf("------------------ LCS Test ( End ) ------------------\n\n");

    // Make a spiral
    printf("------------------ Make A Spiral (Begin) ------------------\n");
    int a[5][5] = {0};
    make_a_spiral(5, a);
    for (int i = 0; i < 5; ++i) {
        for (int k = 0; k < 5; ++k) printf("%d ", a[i][k]);
        printf("\n");
    }
    printf("------------------ Make A Spiral ( End ) ------------------\n\n");

    // sort test
    printf("------------------ Sort Test (Begin) ------------------\n");
    str1 = "pqmpgtzzfaqftdawjqiurwscy";
    str2 = "fevbekrsaanbbsbrzwwbvfsdb";
    char *ex = "2:bbbbbb/1:qqq/2:sss/1:pp/1:tt/1:zz/2:ee/2:rr/2:vv/=:aa/=:ff/=:ww";
    char *test_s1 = calloc(BA_STRLEN(str1) + 1, sizeof(char));
    BA_STRCPY(test_s1, str1);
    bubble_sort_char(test_s1, false);
    printf("%s\n", test_s1);
    free(test_s1);
    printf("------------------ Sort Test ( End ) ------------------\n\n");

    // stack test
    printf("------------------ Stack Test (Begin) ------------------\n");
    long long int cost_time = run_time(COUNT_TIME_US, stack_test);
    run_time_show(&cost_time);
    printf("------------------ Stack Test ( End ) ------------------\n\n");

    // chain test
    printf("------------------ Chain Test (Begin) ------------------\n");
    long long int cost_time2 = run_time(COUNT_TIME_US, chain_test);
    run_time_show(&cost_time2);
    printf("%s\n", CW_KATA_VER);
    printf("------------------ Chain Test ( End ) ------------------\n\n");

    // Queue test
    printf("------------------ Queue Test (Begin) ------------------\n");
    cost_time2 = run_time(COUNT_TIME_US, queue_test);
    run_time_show(&cost_time2);
    printf("%s\n", CW_KATA_VER);
    printf("------------------ Queue Test ( End ) ------------------\n\n");



    // string mix
    printf("------------------ String Mix (Begin) ------------------\n");
    char *res1 = string_mix(str1, str2);
    printf("%s\n", res1);
    free(res1);
    printf("------------------ String Mix ( End ) ------------------\n\n");
}


int main() {

    size_t cost_time2 = run_time(COUNT_TIME_US, hash_test);
    run_time_show(&cost_time2);

    //chain_test();

    // fun_test();
    return 0;
}
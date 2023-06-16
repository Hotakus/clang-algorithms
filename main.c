#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "main.h"
#include "katas/include/num_english.h"

char *str = "hello world asd x2 21 a !";
char *str2 = "hello";
void rgb(int r, int g, int b, char *buf) {
    r = r > 255 ? 255 : (r < 0 ? 0 : r);
    g = g > 255 ? 255 : (g < 0 ? 0 : g);
    b = b > 255 ? 255 : (b < 0 ? 0 : b);
    sprintf(buf, "%02X%02X%02X", r, g, b);
}


int *sort(const int *array, int length)
{
    char **num_str = (char **)calloc(length, sizeof(char*));
    int *res = (int *)calloc(length, sizeof(int));
    for (int i = 0; i < length; ++i) {
        num_str[i] = num2English(array[i]);
    }

    bubble_sort_str_arr(num_str, length, false);

    for (int i = 0; i < length; ++i) {
        printf(".......%s\n", num_str[i]);
    }

    return calloc(length, sizeof(int)); // Do your magic!
}


int main() {
//    char* arr[] = {"one", "two", "three", "four"};
//    int n = sizeof(arr) / sizeof(arr[0]);
//
//    bubble_sort_str_arr(arr, n, false);
//
//    printf("Sorted array:\n");
//    for (int i = 0; i < n; i++) {
//        printf("%s\n", arr[i]);
//    }

    int na[] = {1, 2, 3, 4, 5, 123, 13, 65};
    int na2[] = {9, 99, 999};
    sort(na2, 3);

    for (int i = 0; i <= 999; ++i) {
        char *res = num2English(i);
        printf("%03d : %s\n", i, res);
        num2English_free(res, i);
    }

    /*char *res = num2English(113);
    printf("- %03d : %s\n", 113, res);
    usleep(50 * 1000);
    num2English_free(res, 113);*/

    return 0;
}
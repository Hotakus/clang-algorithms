
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "utilities.h"

int digits(uint64_t num) {
    int digit = 0;
    do {
        num /= 10;
        digit++;
    } while ((num));
    return digit;
}

void num_to_string(char *buf, uint64_t num) {
    uint64_t len = digits(num);
    for (uint64_t i = len; i > 0; --i) {
        buf[i - 1] = (char) (num % 10 + 48);
        num /= 10;
    }
    buf[len] = '\0';
}

void char_swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}


ssize_t alpha_find_times(const char *src, const char ch) {
    ssize_t ascii[128] = {0};
    while (*src) ascii[*src++ - 'a'] += 1;
    return ascii[ch - 'a'];
}

char **str_split(const char *src, char sep, int *wn) {
    if (src == NULL) return NULL;

    char *src2 = (char *) malloc(sizeof(char) * (strlen(src)) + 1);
    strcpy(src2, src);

    int cnt = 0;
    while (*src) if (*src++ == ' ') cnt++;
    cnt += 1;
    *wn = cnt;

    char **tmp = (char **)malloc(sizeof(char*) * cnt);
    memset(tmp, 0, sizeof(char*) * cnt);
    char **pt = tmp;

    *pt = src2;
    char *ps = src2;
    do {
        if (*src2 == sep) {
            *++pt = (src2 + 1);
            *src2++ = '\0';
        }
    } while (*src2++);

    return tmp;
}

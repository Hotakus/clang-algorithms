
#include <stdio.h>
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
    for (uint64_t i = digits(num); i > 0; --i) {
        buf[i - 1] = (char) (num % 10 + 48);
        num /= 10;
    }
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

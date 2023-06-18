#ifndef CODEWAR_KATA_C_UTILITIES_H
#define CODEWAR_KATA_C_UTILITIES_H

#include <stdint.h>
#include <stdbool.h>

#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(x, y)               ((x) > (y) ? (x) : (y))
#define MIN(x, y)               ((x) < (y) ? (x) : (y))
#define ARRAY_SIZE(arr)         (sizeof(arr)/sizeof(arr[0]))

#define IS_TRUE(b)     ((b == true) ? "true" : "false")

// alpha and number
int digits_len(long long int num);
int get_digit(long long int num, unsigned char d);
char *num_to_str(long long int num);
int alpha_find_times(const char *src, char ch);

// str custom
int str_cmp(const char *s1, const char *s2);
void str_cpy(char *dest, const char *src);
int str_len(const char *src);
char *str_conn(char *s1, char *s2);

// str extra
char **str_split(const char *src, char sep, int *wn);
void str_split_free(char **buf);

// miscellaneous



#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_UTILITIES_H

#ifndef CODEWAR_KATA_C_UTILITIES_H
#define CODEWAR_KATA_C_UTILITIES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(x, y)               ((x) > (y) ? (x) : (y))
#define MIN(x, y)               ((x) < (y) ? (x) : (y))
#define ARRAY_SIZE(arr)         (sizeof(arr)/sizeof(arr[0]))


int digits(long long int num);
char *num_to_str(long long int num);
int alpha_find_times(const char *src, char ch);

int str_cmp(const char *s1, const char *s2);
void str_cpy(char *dest, const char *src);
int str_len(const char *src);

char **str_split(const char *src, char sep, int *wn);
void str_split_free(const char **buf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_UTILITIES_H

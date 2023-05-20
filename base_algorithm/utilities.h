#ifndef CODEWAR_KATA_C_UTILITIES_H
#define CODEWAR_KATA_C_UTILITIES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define max(x, y)   ((x) > (y) ? (x) : (y))
#define min(x, y)   ((x) < (y) ? (x) : (y))


uint64_t digits(uint64_t num);
void num_to_string(char *buf, uint64_t num);
void char_swap(char *a, char *b);
ssize_t alpha_find_times(const char *src, char ch);

char **str_split(const char *src, char sep, int *wn);
void str_split_free(const char **buf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_UTILITIES_H

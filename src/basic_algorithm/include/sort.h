#ifndef CODEWAR_KATA_C_SORT_H
#define CODEWAR_KATA_C_SORT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*...*/
// bubble sort function
int *bubble_sort_int( int *src, uint64_t len, bool is_descent);
char *bubble_sort_char(char *src, bool is_descent);
char *bubble_sort_str_arr(char **src, int len, bool is_descent);
void *bubble_sort_void(void *src, bool is_descent);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_SORT_H

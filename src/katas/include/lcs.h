/**
  ******************************************************************************
  * @file           : lcs.h
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/6/30
  ******************************************************************************
  */


#ifndef CODEWAR_KATA_C_LCS_H
#define CODEWAR_KATA_C_LCS_H



#ifdef __cplusplus
extern "C" {
#endif

typedef enum lcs_src_t {
    LCS_SRC_UP, LCS_SRC_LEFT, LCS_SRC_TOP_LEFT
} lcs_src_t;

typedef struct lcs_t {
    const char *str1;
    const char *str2;
    int s1_length;
    int s2_length;
    int **mat;          // lcs matrix
    lcs_src_t **src;    // lcs source path
    char *sub;          // lcs subsequence string
} lcs_t;

lcs_t *lcs_solve(const char *str1, const char *str2);
int lcs_length(lcs_t *lcs);
const char *lcs_body(lcs_t *lcs);
void lcs_free(lcs_t *lcs);
void lcs_show(lcs_t *lcs);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //CODEWAR_KATA_C_LCS_H

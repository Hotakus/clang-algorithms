/**
  ******************************************************************************
  * @file           : lcs.c
  * @author         : Hotakus (hotakus@foxmail.com)
  * @brief          : None
  * @date           : 2023/6/30
  ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include "lcs.h"
#include "../basic_algorithm/config.h"


/**
 *
 * @param str1
 * @param str2
 * @return
 */
lcs_t *lcs_solve(const char *str1, const char *str2) {
    lcs_t *lcs = calloc(1, sizeof(lcs_t));

    lcs->str1 = str1;
    lcs->str2 = str2;
    lcs->s1_length = BA_STRLEN(lcs->str1);
    lcs->s2_length = BA_STRLEN(lcs->str2);

    if (lcs->s1_length == 0 || lcs->s2_length == 0) return NULL;

    lcs->mat = (int **) calloc(lcs->s1_length + 1, sizeof(int *));
    lcs->src = (lcs_src_t **) calloc(lcs->s1_length + 1, sizeof(lcs_src_t *));
    for (int i = 0; i <= lcs->s1_length; ++i) {
        lcs->mat[i] = (int *) calloc(lcs->s2_length + 1, sizeof(int));
        lcs->src[i] = (lcs_src_t *) calloc(lcs->s2_length + 1, sizeof(lcs_src_t));
    }

    for (int i = 1; i <= lcs->s1_length; ++i) {
        for (int j = 1; j <= lcs->s2_length; ++j) {
            if (lcs->str1[i - 1] == lcs->str2[j - 1]) {
                lcs->mat[i][j] = lcs->mat[i - 1][j - 1] + 1;    // 斜角加 1
                lcs->src[i][j] = LCS_SRC_TOP_LEFT;
            } else {
                if (lcs->mat[i - 1][j] > lcs->mat[i][j - 1]) {
                    lcs->mat[i][j] = lcs->mat[i - 1][j];
                    lcs->src[i][j] = LCS_SRC_UP;
                } else {
                    lcs->mat[i][j] = lcs->mat[i][j - 1];
                    lcs->src[i][j] = LCS_SRC_LEFT;
                }
            }
        }
    }

    return lcs;
}

int lcs_length(lcs_t *lcs) {
    if (!lcs || !lcs->mat) return -1;
    return lcs->mat[lcs->s1_length][lcs->s2_length];
}

const char *lcs_body(lcs_t *lcs) {
    int lcs_len = lcs_length(lcs);
    if (!lcs->sub)
        lcs->sub = (char *) calloc(lcs_len + 1, sizeof(char));

    int s1l = lcs->s1_length;
    int s2l = lcs->s2_length;
    for (int i = lcs_len; i > 0;) {
        if (lcs->src[s1l][s2l] == LCS_SRC_TOP_LEFT) {
            lcs->sub[i - 1] = lcs->str1[s1l - 1];
            s1l -= 1;
            s2l -= 1;
            --i;
        } else if (lcs->src[s1l][s2l] == LCS_SRC_LEFT) s2l--;
        else s1l--;
    }

    lcs->sub[lcs_len] = '\0';
    return lcs->sub;
}

void lcs_free(lcs_t *lcs) {
    if (!lcs || !lcs->mat) return;
    for (int i = 0; i < lcs->s1_length + 1; ++i)
        free(lcs->mat[i]);
    free(lcs->mat);

    if (lcs->src) {
        for (int i = 0; i < lcs->s2_length; ++i)
            free(lcs->src[i]);
        free(lcs->src);
    }

    if (lcs->sub)
        free(lcs->sub);
    free(lcs);
}


void lcs_show(lcs_t *lcs) {
    printf("results: \n");
    for (int i = 0; i < lcs->s1_length + 1; ++i) {
        for (int j = 0; j < lcs->s2_length + 1; ++j)
            printf("%d ", lcs->mat[i][j]);
        printf("\n");
    }

    printf("src: \n");
    for (int i = 0; i < lcs->s1_length + 1; ++i) {
        for (int j = 0; j < lcs->s2_length + 1; ++j)
            printf("%d ", lcs->src[i][j]);
        printf("\n");
    }
}

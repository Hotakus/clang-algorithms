/**
  ******************************************************************************
  * @file      : make_a_spiral.h
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/24
  ******************************************************************************
  */

#ifndef CODEWAR_KATA_C_MAKE_A_SPIRAL_H
#define CODEWAR_KATA_C_MAKE_A_SPIRAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum STEP_DIR {
    STEP_RIGHT, STEP_DOWN, STEP_LEFT, STEP_UP
} step_dir_t;

void make_a_spiral(unsigned n, int spiral[n][n]);
const int *snail(size_t *outsz, const int **mx, size_t rows, size_t cols);

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_MAKE_A_SPIRAL_H

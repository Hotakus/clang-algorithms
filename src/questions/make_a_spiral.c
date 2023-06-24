/**
  ******************************************************************************
  * @file      : make_a_spiral.c
  * @author    : Hotakus (ttowfive@gmail.com)
  * @brief     : None
  * @attention : None
  * @date      : 2023/6/24
  ******************************************************************************
  */

#include <stdbool.h>
#include <memory.h>
#include "make_a_spiral.h"


int *step_to(step_dir_t step_dir, int *probe, int col) {
    switch (step_dir) {
        case STEP_RIGHT :   { probe += 1; break; }
        case STEP_LEFT  :   { probe -= 1; break; }
        case STEP_UP    :   { probe -= col; break; }
        case STEP_DOWN  :   { probe += col; break; }
    }
    return probe;
}

void make_a_spiral(unsigned n, int spiral[n][n]) {
    for (int i = 0; i < n; ++i) memset(spiral[i], 0, n * sizeof(int));
    int *probe = &spiral[0][n - 1];
    unsigned row = n;
    unsigned col = n;
    unsigned char gap = 2;
    bool is_odd = n & 0x01;
    unsigned loop_times = (n - 1) + (is_odd ? 0 : 1);
    unsigned step = n - (is_odd ? 0 : 1);

    step_dir_t dir = STEP_DOWN;
    unsigned *sw = &row;
    bool sw_flag = false;
    for (int i = 0; i < n; ++i) spiral[0][i] = 1;
    for (int t = 0; t < loop_times; ++t) {
        // row
        for (int i = 0; i < *sw - 1; ++i) {
            probe = step_to(dir, probe, n);
            *probe = 1;
        }
        *sw -= gap;
        dir += 1;
        step -= 1;

        if (!step) break;
        if (dir > STEP_UP) dir = STEP_RIGHT;
        sw = sw_flag ? (&row) : (&col);
        sw_flag = !sw_flag;
    }
}
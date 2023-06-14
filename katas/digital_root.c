#include "digital_root.h"
#include "../base_algorithm/include/utilities.h"

int digital_root(int n) {
    int res = 0;

    do {
        res += n % 10;
        n = n / 10;
    } while (n != 0);

    return (res > 9) ? digital_root(res) : res;

    // return --n % 9 + 1;
}

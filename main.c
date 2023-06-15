#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char *str = "hello world asd x2 21 a !";
char *str2 = "hello";

void rgb (int r, int g, int b, char *buf)
{
    r = r > 255 ? 255 : (r < 0 ? 0 : r);
    g = g > 255 ? 255 : (g < 0 ? 0 : g);
    b = b > 255 ? 255 : (b < 0 ? 0 : b);
    sprintf(buf, "%02X%02X%02X", r, g, b);
}

int main() {
    chain_test();
}

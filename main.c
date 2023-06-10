#include <stdio.h>
#include <math.h>
#include "main.h"


#include <inttypes.h>
#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include <math.h>


char *str = "hello world asd x2 21 a !";
char *str2 = "hello";

int main() {
    // chain_test();

    int n = 0;
    char **list = str_split(str, ' ', &n);

    printf("%d\n", str_len(str2));

    for (int i = 0; i < n; ++i) {
        printf("%d : %s\n", i, list[i]);
    }

}

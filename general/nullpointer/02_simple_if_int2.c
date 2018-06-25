#include <stdio.h>
#include "nullpointer.h"

void nullpointer_if_else_int2(int x, int y) {
    int arr[3] = {1, 2, 3};
    int* ptr = 0;
    int val, m, n;

    m = -1;
    n = 5;

    x = x*m+n;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    if(x < y) {
        ptr = arr;
    }

    if(x > 10) {
        val = arr[2];
    } else {
        val = ptr[2]; /* DANGER: x <= 10 && x >= y */
    }

    printf("x=%i: %i", x, val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_if_else_int2(-4, 11);
    nullpointer_if_else_int2(-5, 11);
    nullpointer_if_else_int2(-6, 11);
#else
    nullpointer_if_else_int2(-4, 10); /* OK */
    nullpointer_if_else_int2(-5, 10); /* DANGER */
    nullpointer_if_else_int2(-6, 10); /* OK */
#endif

    return 1;
}
#endif

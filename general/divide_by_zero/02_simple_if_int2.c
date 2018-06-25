#include <stdio.h>
#include "divide_by_zero.h"

void divide_zero_if_else_int2(int x, int y) {
    int divisor;
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
        divisor = 1;
    } else {
        divisor = 2;
    }

    if(x > 10) {
        val = 37 / (divisor + 2);
    } else {
        val = 11 / (divisor - 2); /* DANGER, if x <= 10 & x >= y */
    }

    printf("x=%i: %i", x, val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_if_else_int2(-4, 11);
    divide_zero_if_else_int2(-5, 11);
    divide_zero_if_else_int2(-6, 11);
#else
    divide_zero_if_else_int2(-4, 10); /* OK */
    divide_zero_if_else_int2(-5, 10); /* DANGER */
    divide_zero_if_else_int2(-6, 10); /* OK */
#endif

    return 1;
}
#endif

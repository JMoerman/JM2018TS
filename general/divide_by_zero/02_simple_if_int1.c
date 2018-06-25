#include <stdio.h>
#include "divide_by_zero.h"

void divide_zero_if_else_int1(int x, int y) {
    int divisor;
    int val;

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
    divide_zero_if_else_int1(9, 10);
    divide_zero_if_else_int1(10, 11);
    divide_zero_if_else_int1(11, 10);
#else
    divide_zero_if_else_int1(9, 10); /* OK */
    divide_zero_if_else_int1(10, 10); /* DANGER */
    divide_zero_if_else_int1(11, 10); /* OK */
#endif

    return 1;
}
#endif

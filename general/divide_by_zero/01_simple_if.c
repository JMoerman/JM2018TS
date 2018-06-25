#include <stdio.h>
#include <stdbool.h>
#include "divide_by_zero.h"

void divide_zero_if_else(bool a, bool b) {
    int divisor;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    if(a) {
        divisor = 1;
    } else {
        divisor = 2;
    }

    if(b) {
        val = 37 / (divisor + 2);
    } else {
        val = 11 / (divisor - 2); /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_if_else(true, true);
    divide_zero_if_else(true, false);
    divide_zero_if_else(false, true);
#else
    divide_zero_if_else(true, true); /* OK */
    divide_zero_if_else(false, false); /* DANGER */
    divide_zero_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif

#include "divide_by_zero.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>

void divide_zero_cross_file(bool a, bool b) {
    int divisor;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    divisor = choose_int(2, 0, a);

    if(b) {
        val = 10 / (divisor + 2);
    } else {
        val = 10 / divisor; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_cross_file(true, true);
    divide_zero_cross_file(true, false);
    divide_zero_cross_file(false, true);
#else
    divide_zero_cross_file(true, true); /* OK */
    divide_zero_cross_file(false, false); /* DANGER */
    divide_zero_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif

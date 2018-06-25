#include <stdio.h>
#include <limits.h>
#include "integer_overflow.h"

void integer_overflow_rec(int x, int i, int val) {
    if(i <= 1) {
        printf("%i\n", val);
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x > 10) {
        printf("%i\n", val);
        return;
    }
#endif

    if(i < x) {
        val += 10;
    } else {
        val += 1;
    }

    if(i == 10) {
        printf("%i\n", val);
        val = INT_MAX - 10;
    }
    integer_overflow_rec(x, i-1, val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_rec(10, 20, INT_MAX - 110);
#else
    integer_overflow_rec(12, 20, INT_MAX - 110);
#endif

    return 1;
}
#endif

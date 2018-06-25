#include <stdio.h>
#include <limits.h>
#include "integer_overflow.h"

void integer_overflow_pseudo_rec1(int x, int y, int i, int val) {

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    if(i > 0) {
        return;
    }

    if(x > 10) {
        val = INT_MAX - 30;
    } else {
        val = INT_MAX - 10;
    }

    integer_overflow_pseudo_rec2(x, y, 1, val);
}

void integer_overflow_pseudo_rec2(int x, int y, int i, int val) {
    if(i > 0) {
        if(x < y) {
            val += 5;
        } else {
            val += 25;
        }
        printf("%i\n", val);
    } else {
        integer_overflow_pseudo_rec1(x, y, 1, val);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_pseudo_rec1(9, 10, 0, 0);
    integer_overflow_pseudo_rec1(11, 10, 0, 0);
#else
    integer_overflow_pseudo_rec1(10, 10, 0, 0);
#endif

    return 1;
}
#endif

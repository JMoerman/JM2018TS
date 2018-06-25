#include <stdio.h>
#include <limits.h>
#include "integer_overflow.h"

void integer_overflow_for_array(int x) {
    int p[20];
    int val = INT_MAX - 29;
    int incr_ammount = 1;
    int i = 0;

    if(x < 0 || x > 19) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x >= 18) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            val += incr_ammount;
            incr_ammount = 10;
        } else {
            val += incr_ammount;
        }
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_for_array(18);
#else
    integer_overflow_for_array(10);
#endif

    return 1;
}
#endif

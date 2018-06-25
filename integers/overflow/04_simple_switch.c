#include "integer_overflow.h"
#include <limits.h>
#include <stdio.h>

void integer_overflow_switch(int x, int y) {
    int val;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x >= y) {
        return;
    }
#endif

    if(x < y) {
        val = INT_MAX / 4 - 1;
    } else {
        val = INT_MAX / 2 - 1;
    }

    switch (x) {
        case 5: {
            val = val * 3; /* DANGER: x >= y */
            break;
        }
        case 7: {
            val = -val;
            break;
        }
        case 10: {
            val = val * 4; /* DANGER: x >= y */
            break;
        }
        case 12: {
            val = 2 * val;
            break;
        }
        default: {
           val = -2 * val;
            break;
        }
    };

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_switch(5, 11);
    integer_overflow_switch(10, 11);
    integer_overflow_switch(11, 11);
    integer_overflow_switch(7, 5);
#else
    integer_overflow_switch(5, 10); /* OK */
    integer_overflow_switch(10, 10); /* DANGER */
    integer_overflow_switch(11, 10); /* OK */
    integer_overflow_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif

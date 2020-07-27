#include <stdio.h>
#include <limits.h>
#include "integer_overflow.h"

void integer_overflow_goto(int x) {
    int val = INT_MAX / 3 - 1;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

    i = 0;

GOTO_LABEL:
    if(i <= x) {
        printf("%i\n", val * 3);
    } else {
        printf("%i\n", val);
    }

    if(i == 0) {
        i++;
        val = val * 2;
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_goto(0);
#else
    integer_overflow_goto(1);
#endif

    return 1;
}
#endif

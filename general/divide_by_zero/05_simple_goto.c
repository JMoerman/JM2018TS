#include <stdio.h>
#include "divide_by_zero.h"

void divide_zero_goto(int x) {
    int val, i;
    int divisor = 1;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

    val = 37 / 3;
    i = 0;

GOTO_LABEL:
    if(i <= x) {
        val += 10 / (divisor + 1);
    } else {
        printf("%i\n", val);
    }

    divisor -= 2;

    if(i == 0) {
        i++;
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_goto(0);
#else
    divide_zero_goto(1);
#endif

    return 1;
}
#endif

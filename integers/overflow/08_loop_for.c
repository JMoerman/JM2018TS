#include <stdio.h>
#include <limits.h>
#include "integer_overflow.h"

void integer_overflow_for(int x) {
    int val = INT_MAX - 20;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x < 9) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        if(i > x) {
             val += 10; /* DANGER: x < 10 */
        } else {
             val++;
        }
        if(i == 10) {
            val -= 100;
        }
    }
    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_for(9);
#else
    integer_overflow_for(8);
#endif

    return 1;
}
#endif

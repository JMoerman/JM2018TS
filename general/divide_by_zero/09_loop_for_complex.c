#include <stdio.h>
#include "divide_by_zero.h"

void divide_zero_for_complex(int x) {
    int divisor = 2;
    int val = 0, i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    for(;;) {
        if(i > x) {
            val += 10 / (divisor - 2); /* DANGER: x < 10 */
        } else {
            val += 10 / (divisor + 2);
        }
        if(i == 10) {
            divisor = 4;
            val += 10 / divisor;
        }
        i++;
        if(i >= 20) {
            break;
        }
    }

    printf("val = %i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_for_complex(10);
#else
    divide_zero_for_complex(9);
#endif

    return 1;
}
#endif

#include <stdio.h>
#include "uninitialized_value.h"

void uninit_val_while_continue(int x) {
    int possibly_uninit;
    int val = 0, i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    while(i < 30) {
        if(i > x) {
            val += 10 * (possibly_uninit - 2); /* DANGER: x < 10 */
        } else {
            val += 10 * 4;
        }
        if(i == 10) {
            possibly_uninit = 4;
            val += 10 * possibly_uninit;
        }
        i++;
        if(i < 20) {
            continue;
        }
    }

    printf("val = %i", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_while_continue(10);
#else
    uninit_val_while_continue(9);
#endif

    return 1;
}
#endif

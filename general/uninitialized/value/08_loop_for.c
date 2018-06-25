#include <stdio.h>
#include "uninitialized_value.h"

void uninit_val_for(int x) {
    int possibly_uninit;
    int val = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        if(i > x) {
            val += 10 * (possibly_uninit - 2); /* DANGER: x < 10 */
        } else {
            val += 10 * 4;
        }
        if(i == 10) {
            possibly_uninit = 4;
            val += 10 * possibly_uninit;
        }
    }

    printf("val = %i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_for(10);
#else
    uninit_val_for(9);
#endif

    return 1;
}
#endif

#include <stdio.h>
#include "uninitialized_value.h"

void uninit_val_if_else_int1(int x, int y) {
    int possibly_uninit;
    int val;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    if(x < y) {
        possibly_uninit = 1;
    }

    if(x > 10) {
        val = 37 * 2;
    } else {
        val = 11 * possibly_uninit; /* DANGER, if x <= 10 & x >= y */
    }

    printf("x=%i: %i", x, val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_if_else_int1(9, 10);
    uninit_val_if_else_int1(10, 11);
    uninit_val_if_else_int1(11, 10);
#else
    uninit_val_if_else_int1(9, 10); /* OK */
    uninit_val_if_else_int1(10, 10); /* DANGER */
    uninit_val_if_else_int1(11, 10); /* OK */
#endif

    return 1;
}
#endif

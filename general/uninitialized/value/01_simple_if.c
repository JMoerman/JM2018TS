#include <stdio.h>
#include <stdbool.h>
#include "uninitialized_value.h"

void uninit_val_if_else(bool a, bool b) {
    int possibly_uninit;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    if(a) {
        possibly_uninit = 1;
    }

    if(b) {
        val = 37 * 2;
    } else {
        val = 11 * possibly_uninit; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_if_else(true, true);
    uninit_val_if_else(true, false);
    uninit_val_if_else(false, true);
#else
    uninit_val_if_else(true, true); /* OK */
    uninit_val_if_else(false, false); /* DANGER */
    uninit_val_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif

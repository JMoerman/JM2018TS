#include "uninitialized_value.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>

void uninit_val_cross_file(bool a, bool b) {
    int* possibly_uninit;
    int init_value = 5;
    int uninit_value;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    possibly_uninit = (int*) choose_pointer((void*) &init_value, (void*) &uninit_value, a);

    if(b) {
        val = 10 * 2;
    } else {
        val = 10 * (*possibly_uninit); /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_cross_file(true, true);
    uninit_val_cross_file(true, false);
    uninit_val_cross_file(false, true);
#else
    uninit_val_cross_file(true, true); /* OK */
    uninit_val_cross_file(false, false); /* DANGER */
    uninit_val_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif

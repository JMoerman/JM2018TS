#include <stdio.h>
#include <stdbool.h>
#include "uninitialized_value.h"

static void assign_int_ptr(int** dest, int* ptr1, int* ptr2, bool condition) {
    if(condition) {
        *dest = ptr1;
    } else {
        *dest = ptr2;
    }
}

void uninit_val_pass_by_reference(bool a, bool b) {
    int* possibly_uninit;
    int uninit_value;
    int init_value = 5;
    int val;

#ifdef CATCH_BAD_PARAM
    /* To be used if NO_BUG is defined */
    /* and tool warns about possible dangerous input */
    if(!a & !b) {
        return;
    }
#endif

    assign_int_ptr(&possibly_uninit, &init_value, &uninit_value, a);

    if(b) {
        val = 25 * 4;
    } else {
        val = 91 * (*possibly_uninit); /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_pass_by_reference(true, true);
    uninit_val_pass_by_reference(true, false);
    uninit_val_pass_by_reference(false, true);
#else
    uninit_val_pass_by_reference(true, true); /* OK */
    uninit_val_pass_by_reference(false, false); /* DANGER */
    uninit_val_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif

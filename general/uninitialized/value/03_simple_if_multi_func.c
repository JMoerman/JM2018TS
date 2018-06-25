#include "uninitialized_value.h"
#include <stdbool.h>
#include <stdio.h>

static int* choose_int_ptr(int* ptr1, int* ptr2, bool condition) {
    if(condition) {
        return ptr1;
    } else {
        return ptr2;
    }
}

static int conditional_assign(int* ptr1, int* ptr2, bool condition) {
    if(condition) {
        return *ptr1;
    }
    return *ptr2;
}

void uninit_val_if_else_multi(bool a, bool b) {
    int temp_val = 5;
    int uninit_value;
    int* temp_ptr;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    temp_ptr = choose_int_ptr(&temp_val, &uninit_value, a);

    val = conditional_assign(&temp_val, temp_ptr, b); /* DANGER, if !a & !b */

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_if_else_multi(true, true);
    uninit_val_if_else_multi(true, false);
    uninit_val_if_else_multi(false, true);
#else
    uninit_val_if_else_multi(true, true); /* OK */
    uninit_val_if_else_multi(false, false); /* DANGER */
    uninit_val_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif

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

void uninit_val_function_pointer(bool a, bool b, void (*f)(int**, int*, int*, bool)) {
    int* possibly_uninit;
    int uninit_val;
    int init_val = 7;
    int val;

#ifdef CATCH_BAD_PARAM
    /* To be used if NO_BUG is defined */
    /* and tool warns about possible dangerous input */
    if(!f || (!a & !b)) {
        return;
    }
#endif

    (*f)(&possibly_uninit, &init_val, &uninit_val, a);

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
    uninit_val_function_pointer(true, true, &assign_int_ptr);
    uninit_val_function_pointer(true, false, &assign_int_ptr);
    uninit_val_function_pointer(false, true, &assign_int_ptr);
#else
    uninit_val_function_pointer(true, true, &assign_int_ptr); /* OK */
    uninit_val_function_pointer(false, false, &assign_int_ptr); /* DANGER */
    uninit_val_function_pointer(false, true, &assign_int_ptr); /* OK */
#endif

    return 1;
}
#endif

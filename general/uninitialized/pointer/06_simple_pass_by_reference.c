#include <stdio.h>
#include <stdbool.h>
#include "uninit_ptr.h"

static void local_assign_pointer(int*** dest, int** source1, int** source2, bool condition) {
    if(condition) {
        *dest = source1;
    } else {
        *dest = source2;
    }
}

void uninit_ptr_pass_by_reference(bool a, bool b) {
    int arr[3] = {1, 2, 3};
    int* arr_allias = arr;
    int** ptr;
    int* uninit;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    local_assign_pointer(&ptr, &arr_allias, &uninit, a);

    if(b) {
        val = arr[2];
    } else {
        val = **ptr; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_ptr_pass_by_reference(true, true);
    uninit_ptr_pass_by_reference(true, false);
    uninit_ptr_pass_by_reference(false, true);
#else
    uninit_ptr_pass_by_reference(true, true); /* OK */
    uninit_ptr_pass_by_reference(false, false); /* DANGER */
    uninit_ptr_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif

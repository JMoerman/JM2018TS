#include <stdio.h>
#include <stdbool.h>
#include "uninit_ptr.h"

void uninit_ptr_if_else(bool a, bool b) {
    int arr[3] = {1, 2, 3};
    int* ptr;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    if(a) {
        ptr = arr;
    }

    if(b) {
        val = arr[2];
    } else {
        val = ptr[2]; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_ptr_if_else(true, true);
    uninit_ptr_if_else(true, false);
    uninit_ptr_if_else(false, true);
#else
    uninit_ptr_if_else(true, true); /* OK */
    uninit_ptr_if_else(false, false); /* DANGER */
    uninit_ptr_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif

#include <stdio.h>
#include <stdbool.h>
#include "nullpointer.h"

void nullpointer_if_else(bool a, bool b) {
    int arr[3] = {1, 2, 3};
    int* ptr = 0;
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
    nullpointer_if_else(true, true);
    nullpointer_if_else(true, false);
    nullpointer_if_else(false, true);
#else
    nullpointer_if_else(true, true); /* OK */
    nullpointer_if_else(false, false); /* DANGER */
    nullpointer_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif

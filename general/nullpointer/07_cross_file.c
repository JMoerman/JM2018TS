#include "nullpointer.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>

void nullpointer_cross_file(bool a, bool b) {
    int arr[3] = {1, 2, 3};
    int* ptr = 0;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    ptr = (int*)choose_pointer((void*)(arr+1), 0, a);

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
    nullpointer_cross_file(true, true);
    nullpointer_cross_file(true, false);
    nullpointer_cross_file(false, true);
#else
    nullpointer_cross_file(true, true); /* OK */
    nullpointer_cross_file(false, false); /* DANGER */
    nullpointer_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif

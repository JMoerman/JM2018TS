#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uninitialized_malloc.h"

void uninit_malloc_if_else(bool a, bool b) {
    int* data;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    if(a) {
        *data = 1;
    }

    if(b) {
        val = 37 * 2;
    } else {
        val = 11 * *data; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);

    free(data);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_malloc_if_else(true, true);
    uninit_malloc_if_else(true, false);
    uninit_malloc_if_else(false, true);
#else
    uninit_malloc_if_else(true, true); /* OK */
    uninit_malloc_if_else(false, false); /* DANGER */
    uninit_malloc_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif

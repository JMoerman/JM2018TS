#include "uninitialized_malloc.h"
#include "common.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void uninit_malloc_cross_file(bool a, bool b) {
    int* data;
    int val;
    int* int_ptr;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    int_ptr = (int*) choose_pointer((void*) data, (void*) &val, a);
    *int_ptr = 768;

    if(b) {
        val = 10 * 2;
    } else {
        val = 10 * *data; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
    free(data);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_malloc_cross_file(true, true);
    uninit_malloc_cross_file(true, false);
    uninit_malloc_cross_file(false, true);
#else
    uninit_malloc_cross_file(true, true); /* OK */
    uninit_malloc_cross_file(false, false); /* DANGER */
    uninit_malloc_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif

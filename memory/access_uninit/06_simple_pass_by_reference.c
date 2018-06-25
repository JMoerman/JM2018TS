#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uninitialized_malloc.h"

static void possibly_assign(int** dest, int val, bool condition) {
    if(condition) {
        **dest = val;
    }
}

void uninit_malloc_pass_by_reference(bool a, bool b) {
    int* data;

#ifdef CATCH_BAD_PARAM
    /* To be used if NO_BUG is defined */
    /* and tool warns about possible dangerous input */
    if(!a & !b) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    possibly_assign(&data, 5, a);
    possibly_assign(&data, 13, b);

    printf("%i\n", *data);

    free(data);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_malloc_pass_by_reference(true, true);
    uninit_malloc_pass_by_reference(true, false);
    uninit_malloc_pass_by_reference(false, true);
#else
    uninit_malloc_pass_by_reference(true, true); /* OK */
    uninit_malloc_pass_by_reference(false, false); /* DANGER */
    uninit_malloc_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif

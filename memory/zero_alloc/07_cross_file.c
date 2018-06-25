#include "zero_alloc.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void zero_alloc_cross_file(bool a, bool b) {
    size_t size;
    int* data;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    size = sizeof(int) * choose_int(2, 0, a);

    if(b) {
        data = malloc(size + sizeof(int));
    } else {
        data = malloc(size); /* DANGER, if !a & !b */
    }

    if(data) {

    }

    if(data) {
        *data = 34;
        printf("%i\n", *data);
        free(data);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_cross_file(true, true);
    zero_alloc_cross_file(true, false);
    zero_alloc_cross_file(false, true);
#else
    zero_alloc_cross_file(true, true); /* OK */
    zero_alloc_cross_file(false, false); /* DANGER */
    zero_alloc_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zero_alloc.h"

static void assign_size(size_t* size, size_t size1, size_t size2, bool use_first) {
    if(use_first) {
        *size = size1;
    } else {
        *size = size2;
    }
}

void zero_alloc_pass_by_reference(bool a, bool b) {
    int* data;
    size_t size;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    assign_size(&size, sizeof(int) * 2, sizeof(int), a);

    if(b) {
        data = malloc(size);
    } else {
        data = malloc(size - sizeof(int)); /* DANGER, if !a & !b */
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
    zero_alloc_pass_by_reference(true, true);
    zero_alloc_pass_by_reference(true, false);
    zero_alloc_pass_by_reference(false, true);
#else
    zero_alloc_pass_by_reference(true, true); /* OK */
    zero_alloc_pass_by_reference(false, false); /* DANGER */
    zero_alloc_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif

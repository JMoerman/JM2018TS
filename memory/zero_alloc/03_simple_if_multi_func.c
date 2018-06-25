#include "zero_alloc.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static size_t choose_size(int size1, int size2, bool return_first) {
    if(return_first) {
        return size1;
    }
    return size2;
}

static void* malloc_conditional_size(size_t size1, size_t size2, bool use_first) {
    if(use_first) {
        return malloc(size1);
    } else {
        return malloc(size2);
    }
}

void zero_alloc_if_else_multi(bool a, bool b) {
    size_t size;
    int* data;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    size = choose_size(sizeof(int), 0, a);
    data = (int*) malloc_conditional_size(size + sizeof(int), size * 3, b); /* DANGER, if !a & !b */

    if(data) {
        *data = 34;
        printf("%i\n", *data);
        free(data);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_if_else_multi(true, true);
    zero_alloc_if_else_multi(true, false);
    zero_alloc_if_else_multi(false, true);
#else
    zero_alloc_if_else_multi(true, true); /* OK */
    zero_alloc_if_else_multi(false, false); /* DANGER */
    zero_alloc_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif

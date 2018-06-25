#include "zero_alloc.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef s_MEMORY_ZA_REFCOUNT
#define s_MEMORY_ZA_REFCOUNT
void zero_alloc_cont_init(SizeCont* cont) {
    cont->refc = 1;
    cont->size = 0;
}

SizeCont* zero_alloc_cont_new() {
    SizeCont* new_cont;

    new_cont = malloc(sizeof(SizeCont));

    if(new_cont) {
        zero_alloc_cont_init(new_cont);
    }
    return new_cont;
}

void zero_alloc_cont_ref(SizeCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void zero_alloc_cont_unref(SizeCont* cont) {
    if(cont->refc <= 1) {
        cont->size = 0;
    } else {
        cont->refc--;
    }
}

size_t zero_alloc_cont_get_size(SizeCont* cont) {
    return cont->size;
}
void zero_alloc_cont_set_size(SizeCont* cont, size_t size) {
    cont->size = size;
}
#endif //s_MEMORY_ZA_REFCOUNT

#ifndef NO_MAIN
int main() {
    SizeCont* cont;
    int* data;

    cont = zero_alloc_cont_new();
    if(!cont) {
        return 1;
    }
    zero_alloc_cont_set_size(cont, 5 * sizeof(int));

    zero_alloc_cont_ref(cont);
    zero_alloc_cont_ref(cont);
    zero_alloc_cont_unref(cont);
    zero_alloc_cont_unref(cont);
#ifdef NO_BUG
    data = malloc(zero_alloc_cont_get_size(cont));
    zero_alloc_cont_unref(cont);
#else
    zero_alloc_cont_unref(cont);
    data = malloc(zero_alloc_cont_get_size(cont));
#endif
    free(cont);

    if(data) {
        *data = 1234;
        printf("%i\n", *data);
        free(data);
    }

    return 1;
}
#endif

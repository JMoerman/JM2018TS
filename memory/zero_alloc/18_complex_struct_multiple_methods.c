#include <stdio.h>
#include <stdlib.h>
#include "zero_alloc.h"

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

void zero_alloc_struct(int x, int y) {
    SizeCont cont;
    int* data;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x > y) {
        return;
    }
#endif

    zero_alloc_cont_init(&cont);
    if(x > y) {
        zero_alloc_cont_set_size(&cont, sizeof(int));
    } else {
        zero_alloc_cont_set_size(&cont, 2 * sizeof(int));
    }


    if(x > 10) {
        data = malloc(zero_alloc_cont_get_size(&cont));
    } else {
        data = malloc(zero_alloc_cont_get_size(&cont) - sizeof(int)); /* DANGER: if x <= 10 & x > y */
    }

    if(data) {
        *data = 37;
        printf("%i\n", *data);
        free(data);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_struct(9, 10);
    zero_alloc_struct(10, 11);
    zero_alloc_struct(11, 10);
#else
    zero_alloc_struct(10, 9); /* DANGER */
#endif

    return 1;
}
#endif

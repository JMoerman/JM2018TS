#include <stdio.h>
#include <stdlib.h>
#include "nullpointer.h"

#ifndef s_NULLPOINTER_REFCOUNT
#define s_NULLPOINTER_REFCOUNT
NRefCont* null_ref_cont_new() {
    NRefCont* new_cont;

    new_cont = malloc(sizeof(NRefCont));

    if(new_cont) {
        new_cont->refc = 1;
        new_cont->p_data = 0;
    }
    return new_cont;
}

void null_ref(NRefCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void null_unref(NRefCont* cont) {
    if(cont->refc <= 1) {
        if(cont->p_data) {
            cont->p_data = 0;
        }
    } else {
        cont->refc--;
    }
}

void* null_ref_cont_get_pointer(NRefCont* cont) {
    return cont->p_data;
}
void null_ref_cont_set_pointer(NRefCont* cont, void* p) {
    cont->p_data = p;
}
#endif //s_NULLPOINTER_REFCOUNT

void nullpointer_struct(int x, int y) {
    int* data;
    int val;
    NRefCont cont;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    null_ref_cont_set_pointer(&cont, 0);

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    *data = 37;

    if(x < y) {
        null_ref_cont_set_pointer(&cont, data);
    }

    if(x > 10) {
        val = *data;
    } else {
        /* DANGER: if x <= 10 & x >= y */
        val = *((int*) null_ref_cont_get_pointer(&cont));
    }

    printf("x=%i: %i", x, val);
    free(data);
}

#ifndef NO_MAIN
int main() {

#ifdef NO_BUG
    nullpointer_struct(9, 10);
    nullpointer_struct(10, 11);
    nullpointer_struct(11, 10);
#else
    nullpointer_struct(10, 10); /* DANGER */
#endif

    return 1;
}
#endif

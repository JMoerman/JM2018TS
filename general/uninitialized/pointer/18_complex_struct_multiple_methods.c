#include <stdio.h>
#include <stdlib.h>
#include "uninit_ptr.h"

#ifndef s_UNINITIALIZED_P_REFCOUNT
#define s_UNINITIALIZED_P_REFCOUNT
void init_uninit_ref_cont(URefCont* cont) {
    cont->refc = 1;
    cont->data_ptr = &(cont->data);
}

URefCont* uninit_ref_cont_new() {
    URefCont* new_cont;

    new_cont = malloc(sizeof(URefCont));

    if(new_cont) {
        init_uninit_ref_cont(new_cont);
    }
    return new_cont;
}

void uninit_ref(URefCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void uninit_unref(URefCont* cont) {
    if(cont->refc <= 1) {
        cont->data_ptr = &(cont->uninit);
    } else {
        cont->refc--;
    }
}

void* uninit_ref_cont_get_pointer(URefCont* cont) {
    return *(cont->data_ptr);
}
void uninit_ref_cont_set_pointer(URefCont* cont, void* p) {
    cont->data = p;
}
#endif //s_UNINITIALIZED_P_REFCOUNT

void uninit_ptr_struct(int x, int y) {
    URefCont cont;
    int* data;
    int val;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    init_uninit_ref_cont(&cont);

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    *data = 37;

    if(x < y) {
        uninit_ref_cont_set_pointer(&cont, data);
    }

    if(x > 10) {
        val = *data;
    } else {
        /* DANGER: if x <= 10 & x >= y */
        val = *((int*) uninit_ref_cont_get_pointer(&cont));
    }

    printf("x=%i: %i", x, val);
    free(data);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_ptr_struct(9, 10);
    uninit_ptr_struct(10, 11);
    uninit_ptr_struct(11, 10);
#else
    uninit_ptr_struct(10, 10); /* DANGER */
#endif

    return 1;
}
#endif

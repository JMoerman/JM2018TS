#include "uninit_ptr.h"
#include <stdlib.h>
#include <stdio.h>

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

#ifndef NO_MAIN
int main() {
    URefCont* cont;
    int arr[3] = {1, 2, 3};
    int val;

    cont = uninit_ref_cont_new();
    if(!cont) {
        return 1;
    }
    uninit_ref_cont_set_pointer(cont, arr);

    uninit_ref(cont);
    uninit_ref(cont);
    uninit_unref(cont);
    uninit_unref(cont);
#ifndef NO_BUG
    uninit_unref(cont);
#endif

    val = *((int*) uninit_ref_cont_get_pointer(cont));

    printf("%i\n", val);

    free(cont);

    return 1;
}
#endif

#include "double_free.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef s_MEMORY_DF_REFCOUNT
#define s_MEMORY_DF_REFCOUNT
void double_free_cont_init(DRefCont* cont) {
    cont->refc = 1;
    cont->data = 0;
}

DRefCont* double_free_cont_new() {
    DRefCont* new_cont;

    new_cont = malloc(sizeof(DRefCont));

    if(new_cont) {
        double_free_cont_init(new_cont);
    }
    return new_cont;
}

void double_free_cont_ref(DRefCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void double_free_cont_unref(DRefCont* cont) {
    if(cont->refc <= 1) {
        free(cont);
    } else {
        cont->refc--;
    }
}

void* double_free_cont_get_pointer(DRefCont* cont) {
    return cont->data;
}
void double_free_cont_set_pointer(DRefCont* cont, void* p) {
    cont->data = p;
}
#endif //s_MEMORY_DF_REFCOUNT

#ifndef NO_MAIN
int main() {
    DRefCont* cont;
    int arr[1] = {99};
    int val;

    cont = double_free_cont_new();
    if(!cont) {
        return 1;
    }
    double_free_cont_set_pointer(cont, arr);

    double_free_cont_ref(cont);
    double_free_cont_ref(cont);
    double_free_cont_unref(cont);
    double_free_cont_unref(cont);
    val = *((int*) double_free_cont_get_pointer(cont));
#ifndef NO_BUG
    double_free_cont_unref(cont);
#endif

    printf("%i\n", val);

    free(cont);

    return 1;
}
#endif

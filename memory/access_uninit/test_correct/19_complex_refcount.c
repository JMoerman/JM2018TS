#include "uninitialized_malloc.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef s_UNINIT_VAL_REFCOUNT
#define s_UNINIT_VAL_REFCOUNT
void uninit_malloc_cont_init(MallocIntCont* cont) {
    cont->counter = 1;
    cont->data = malloc(sizeof(int));
}

MallocIntCont* uninit_malloc_cont_new() {
    MallocIntCont* new_cont;

    new_cont = malloc(sizeof(MallocIntCont));

    if(new_cont) {
        uninit_malloc_cont_init(new_cont);
    }
    return new_cont;
}

void uninit_malloc_cont_incr(MallocIntCont* cont) {
    if(cont) {
        cont->counter++;
    }
}
void uninit_malloc_cont_decr(MallocIntCont* cont) {
    if(cont->counter <= 1) {
        if(cont->data) {
           free(cont->data);
        }
        cont->data = malloc(sizeof(int));
    } else {
        cont->counter--;
    }
}

void uninint_val_cont_free(MallocIntCont* cont) {
    if(cont->data) {
        free(cont->data);
    }
    free(cont);
}

int uninit_malloc_cont_get_value(MallocIntCont* cont) {
    if(cont->data) {
        return *(cont->data);
    }
    return 0;
}
void uninit_malloc_cont_set_value(MallocIntCont* cont, int value) {
    if(!cont->data) {
        return;
    }
    *(cont->data) = value;
}
#endif //s_UNINIT_VAL_REFCOUNT

int main() {
    MallocIntCont* cont;
    int val;

    cont = uninit_malloc_cont_new();
    if(!cont) {
        return 1;
    }
    uninit_malloc_cont_set_value(cont, 35);

    uninit_malloc_cont_incr(cont);
    uninit_malloc_cont_incr(cont);
    uninit_malloc_cont_decr(cont);
    uninit_malloc_cont_decr(cont);

    val = 30 * uninit_malloc_cont_get_value(cont);

    printf("%i\n", val);

    uninint_val_cont_free(cont);

    return 1;
}

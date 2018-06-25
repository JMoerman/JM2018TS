#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

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

void uninit_malloc_struct(int x, int y) {
    MallocIntCont cont;
    int val;

    if(x <= 10 && x >= y) {
        return;
    }

    uninit_malloc_cont_init(&cont);

    if(x < y) {
        uninit_malloc_cont_set_value(&cont, 7);
    }

    if(x > 10) {
        val = 50 * 37;
    } else {
        /* DANGER: if x <= 10 & x >= y */
        val = 30 * uninit_malloc_cont_get_value(&cont);
    }

    if(cont.data) {
        free(cont.data);
    }

    printf("x=%i: %i\n", x, val);
}

int main() {
    uninit_malloc_struct(9, 10);
    uninit_malloc_struct(10, 11);
    uninit_malloc_struct(11, 10);

    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_value.h"

#ifndef s_UNINIT_VAL_REFCOUNT
#define s_UNINIT_VAL_REFCOUNT
void uninit_val_cont_init(DivideCont* cont) {
    cont->counter = 1;
    cont->possibly_uninit = &(cont->init_val);
}

DivideCont* uninit_val_cont_new() {
    DivideCont* new_cont;

    new_cont = malloc(sizeof(DivideCont));

    if(new_cont) {
        uninit_val_cont_init(new_cont);
    }
    return new_cont;
}

void uninit_val_cont_incr(DivideCont* cont) {
    if(cont) {
        cont->counter++;
    }
}
void uninit_val_cont_decr(DivideCont* cont) {
    if(cont->counter <= 1) {
        cont->possibly_uninit = &(cont->uninit_val);
    } else {
        cont->counter--;
    }
}

int uninit_val_cont_get_value(DivideCont* cont) {
    return *(cont->possibly_uninit);
}
void uninit_val_cont_set_value(DivideCont* cont, int value) {
    cont->init_val = value;
}
#endif //s_UNINIT_VAL_REFCOUNT

void uninit_val_struct(int x, int y) {
    DivideCont cont;
    int val;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    uninit_val_cont_init(&cont);

    if(x < y) {
        uninit_val_cont_set_value(&cont, 7);
    }

    if(x > 10) {
        val = 50 * 37;
    } else {
        /* DANGER: if x <= 10 & x >= y */
        val = 30 * uninit_val_cont_get_value(&cont);
    }

    printf("x=%i: %i\n", x, val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_struct(9, 10);
    uninit_val_struct(10, 11);
    uninit_val_struct(11, 10);
#else
    uninit_val_struct(10, 10); /* DANGER */
#endif

    return 1;
}
#endif

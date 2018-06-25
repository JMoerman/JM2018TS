#include "uninitialized_value.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef s_UNINITIALIZED_P_REFCOUNT
#define s_UNINITIALIZED_P_REFCOUNT
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
#endif //s_UNINITIALIZED_P_REFCOUNT

#ifndef NO_MAIN
int main() {
    DivideCont* cont;
    int val;

    cont = uninit_val_cont_new();
    if(!cont) {
        return 1;
    }
    uninit_val_cont_set_value(cont, 35);

    uninit_val_cont_incr(cont);
    uninit_val_cont_incr(cont);
    uninit_val_cont_decr(cont);
    uninit_val_cont_decr(cont);
#ifndef NO_BUG
    uninit_val_cont_decr(cont);
#endif

    val = 30 * uninit_val_cont_get_value(cont);

    printf("%i\n", val);

    free(cont);

    return 1;
}
#endif

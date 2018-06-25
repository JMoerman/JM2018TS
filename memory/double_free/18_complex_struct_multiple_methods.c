#include <stdio.h>
#include <stdlib.h>
#include "double_free.h"

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

void double_free_struct(int x, int y) {
    DRefCont cont;
    int* data;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x > y) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    double_free_cont_init(&cont);
    double_free_cont_set_pointer(&cont, data);

    *data = 37;

    if(x > y) {
        free(data);
    }

    if(x > 10) {
        if(x <= y) {
            free(double_free_cont_get_pointer(&cont));
        }
    } else {
        free(double_free_cont_get_pointer(&cont)); /* DANGER: if x <= 10 & x > y */
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_struct(9, 10);
    double_free_struct(10, 11);
    double_free_struct(11, 10);
#else
    double_free_struct(10, 9); /* DANGER */
#endif

    return 1;
}
#endif

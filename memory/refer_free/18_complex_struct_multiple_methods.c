#include <stdio.h>
#include <stdlib.h>
#include "refer_free.h"

#ifndef s_NULLPOINTER_REFCOUNT
#define s_NULLPOINTER_REFCOUNT
void refer_free_cont_init(RRefCont* cont) {
    cont->refc = 1;
    cont->data = 0;
}

RRefCont* refer_free_cont_new() {
    RRefCont* new_cont;

    new_cont = malloc(sizeof(RRefCont));

    if(new_cont) {
        refer_free_cont_init(new_cont);
    }
    return new_cont;
}

void refer_free_cont_ref(RRefCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void refer_free_cont_unref(RRefCont* cont) {
    if(cont->refc <= 1) {
        free(cont);
    } else {
        cont->refc--;
    }
}

void* refer_free_cont_get_pointer(RRefCont* cont) {
    return cont->data;
}
void refer_free_cont_set_pointer(RRefCont* cont, void* p) {
    cont->data = p;
}
#endif //s_NULLPOINTER_REFCOUNT

void refer_free_struct(int x, int y) {
    RRefCont cont;
    int* data;
    int val = 78;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x > y) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    refer_free_cont_init(&cont);
    refer_free_cont_set_pointer(&cont, data);

    *data = 37;

    if(x > y) {
        free(data);
    }

    if(x <= 10) {
        val = *((int*) refer_free_cont_get_pointer(&cont)); /* DANGER: if x <= 10 & x > y */
    }

    if(x <= y) {
        free(data);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_struct(9, 10);
    refer_free_struct(10, 11);
    refer_free_struct(11, 10);
#else
    refer_free_struct(10, 9); /* DANGER */
#endif

    return 1;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include "memory_leak.h"

#ifndef s_MEMORY_L_REFCOUNT
#define s_MEMORY_L_REFCOUNT
void mem_leak_cont_init(LRefCont* cont) {
    cont->refc = 1;
    cont->data = 0;
}

LRefCont* mem_leak_cont_new() {
    LRefCont* new_cont;

    new_cont = malloc(sizeof(LRefCont));

    if(new_cont) {
        mem_leak_cont_init(new_cont);
    }
    return new_cont;
}

void mem_leak_cont_ref(LRefCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void mem_leak_cont_unref(LRefCont* cont) {
    if(cont->refc <= 1) {
        free(cont);
    } else {
        cont->refc--;
    }
}

void* mem_leak_cont_get_pointer(LRefCont* cont) {
    return cont->data;
}
void mem_leak_cont_set_pointer(LRefCont* cont, void* p) {
    cont->data = p;
}
#endif //s_MEMORY_L_REFCOUNT

void mem_leak_struct(int x, int y) {
    LRefCont cont;
    int* data;
    int val = 78;

#ifdef CATCH_BAD_PARAM
    if(x > 10 && x <= y) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    mem_leak_cont_init(&cont);
    mem_leak_cont_set_pointer(&cont, data);

    *data = 37;

    if(x > y) {
        free(data);
        data = 0;
    }

    if(x <= 10) {
        if(data) {
            val = *data;
            free(mem_leak_cont_get_pointer(&cont));
        }
    } else {
        val = val * 2;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_struct(9, 10);
    mem_leak_struct(10, 11);
    mem_leak_struct(11, 10);
#else
    mem_leak_struct(11, 11); /* DANGER */
#endif

    return 1;
}
#endif

#include <stdlib.h>
#include <stdio.h>
#include "uninitialized_malloc.h"

void uninit_malloc_for_pointer(int x) {
    int* pointers[10];
    int** pointers_alias = pointers;
    int val = 0, i;

    if(x < 0 || x > 10) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    for(i = 0; i < 10; i++, pointers_alias++) {
        *pointers_alias = malloc(sizeof(int));
    }

    pointers_alias = pointers;
    for(i = 0; i < x; i++, pointers_alias++) {
        if(!(*pointers_alias)) {
            continue;
        }
        **pointers_alias = i;
    }

    pointers_alias = pointers;
    for(i = 0; i < 10; i++, pointers_alias++) {
        if(!(*pointers_alias)) {
            continue;
        }
        val += **pointers_alias;
        free(*pointers_alias);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_malloc_for_pointer(10);
#else
    uninit_malloc_for_pointer(9);
#endif

    return 1;
}
#endif

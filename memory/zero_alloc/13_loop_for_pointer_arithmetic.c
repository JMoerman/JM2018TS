#include <stdlib.h>
#include <stdio.h>
#include "zero_alloc.h"

static void initialize_to_value(size_t* ptr, size_t val, int length) {
    int i;

    for(i = 0; i < length; i++, ptr++) {
        *ptr = val;
    }
}

static void free_array(int* ptr_arr[], int length) {
    int i;

    for(i = 0; i < length; i++) {
        if(ptr_arr[i]) free(ptr_arr[i]);
    }
}

void zero_alloc_for_pointer(int x) {
    int* pointers[10];
    int** pointers_alias = pointers;
    size_t sizes[10];
    size_t* ptr = sizes;
    int val = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_to_value(sizes, 0, 10);
    initialize_to_value(sizes, sizeof(int), x);

    for(i = 0; i < 10; i++, ptr++) {
        pointers[i] = malloc(*ptr);
        if(pointers[i]) {
            *pointers[i] = i;
        }
    }

    for(i = 0; i < 10; i++, pointers_alias++) {
        if(*pointers_alias) {
            val += **pointers_alias;
            free(*pointers_alias);
        }
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_for_pointer(10);
#else
    zero_alloc_for_pointer(9);
#endif

    return 1;
}
#endif

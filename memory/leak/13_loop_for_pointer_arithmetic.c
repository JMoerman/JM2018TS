#include <stdlib.h>
#include <stdio.h>
#include "memory_leak.h"

static void initialize_array(int* ptr_arr[], int length) {
    int i;
    int** ptr = ptr_arr;

    for(i = 0; i < length; i++, ptr++) {
        *ptr = malloc(sizeof(int));
        if(*ptr) **ptr = i;
    }
}

static void free_array(int* ptr_arr[], int length) {
    int i;
    int** ptr = ptr_arr;

    for(i = 0; i < length; i++, ptr++) {
        if(*ptr) free(*ptr);
    }
}

void mem_leak_for_pointer(int x) {
    int* pointers[10];
    int** ptr;
    int source[10];
    int val = 0, i;

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_array(pointers, 10);
    ptr = pointers;
    for(int i = 0; i < 10; i++, ptr++) {
        if(*ptr) {
            val += **ptr;
        } else {
            val--;
        }
    }

    free_array(pointers, x);
    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_for_pointer(10);
#else
    mem_leak_for_pointer(9);
#endif

    return 1;
}
#endif

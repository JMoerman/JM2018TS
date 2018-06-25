#include <stdlib.h>
#include <stdio.h>
#include "double_free.h"

static void initialize_array(int* ptr_arr[], int length) {
    int i;

    for(i = 0; i < length; i++) {
        ptr_arr[i] = malloc(sizeof(int));
        if(ptr_arr[i]) *ptr_arr[i] = i;
    }
}

static void free_array(int* ptr_arr[], int length) {
    int i;

    for(i = 0; i < length; i++) {
        if(ptr_arr[i]) free(ptr_arr[i]);
    }
}

void double_free_for_pointer(int x) {
    int* pointers[10];

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_array(pointers, 10);
    free_array(pointers, 10);
    initialize_array(pointers, x);
    free_array(pointers, 10);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_for_pointer(10);
#else
    double_free_for_pointer(9);
#endif

    return 1;
}
#endif

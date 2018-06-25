#include <stdlib.h>
#include <stdio.h>
#include "resource_leak.h"

static void initialize_array(FILE* ptr_arr[], int length) {
    int i;
    FILE** ptr = ptr_arr;

    for(i = 0; i < length; i++, ptr++) {
        *ptr = fopen("file.txt","r");
    }
}

static void close_array(FILE* ptr_arr[], int length) {
    int i;
    FILE** ptr = ptr_arr;

    for(i = 0; i < length; i++, ptr++) {
        if(*ptr) fclose(*ptr);
    }
}

void res_leak_for_pointer(int x) {
    FILE* pointers[10];
    FILE** ptr;
    int val = 0, i;

    if(x > 10) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_array(pointers, 10);
    ptr = pointers;
    for(int i = 0; i < 10; i++, ptr++) {
        if(*ptr) {
            val += (int) fgetc(*ptr);
        } else {
            val--;
        }
    }

    close_array(pointers, x);
    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_for_pointer(10);
#else
    res_leak_for_pointer(9);
#endif

    return 1;
}
#endif

#include <stdlib.h>
#include <stdio.h>
#include "access_closed.h"

static void initialize_array(FILE* ptr_arr[], int length) {
    int i;
    FILE** ptr = ptr_arr;

    for(i = 0; i < length; i++, ptr++) {
        *ptr = fopen("file.txt","r");
    }
}

static void close_backwards(FILE** ptr, int to_close) {
    int i;

    for(i = 0; i < to_close; i++, ptr--) {
        if(*ptr) fclose(*ptr);
    }
}

static void close_forwards(FILE** ptr, int to_close) {
    int i;

    for(i = 0; i < to_close; i++, ptr++) {
        if(*ptr) fclose(*ptr);
    }
}

void access_closed_for_pointer(int x) {
    FILE* pointers[10];
    FILE** ptr;
    int val = 0, i;

    if(x > 10 || x < 0) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x > 5) {
        return;
    }
#endif

    initialize_array(pointers, 10);
    close_backwards(pointers + 9, x);

    ptr = pointers;
    for(int i = 0; i < 5; i++, ptr++) {
        if(*ptr) {
            val += (int) fgetc(*ptr);
        } else {
            val--;
        }
    }

    close_forwards(pointers, 10 - x);
    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_for_pointer(4);
#else
    access_closed_for_pointer(6);
#endif

    return 1;
}
#endif

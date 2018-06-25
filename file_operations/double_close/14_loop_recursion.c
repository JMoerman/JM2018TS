#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "double_close.h"

int double_close_rec(int x, int i, FILE** file_ptr) {
    int val;

#ifdef CATCH_BAD_PARAM
    if(x > 10 && i >= 19) {
        return -1;
    }
#endif

    if(i <= 1) {
        if(*file_ptr) fclose(*file_ptr);
        *file_ptr = 0;
        return 0;
    }

    if(i > 19 && !*file_ptr) {
        *file_ptr = fopen("file.txt", "r");
        return double_close_rec(x, i-1, file_ptr);
    }
    if(i == 19) {
        if(*file_ptr) {
            fclose(*file_ptr);
        }
        return double_close_rec(x, i-1, file_ptr);
    }

    if(i < x) {
        fclose(*file_ptr);
        *file_ptr = fopen("file.txt","r");
        if(!*file_ptr) {
            return -1;
        }
        val = (int) fgetc(*file_ptr);
    } else {
        val = 8;
    }
    if(i == 10 && !*file_ptr) {
        *file_ptr = fopen("file.txt","r");
        if(!*file_ptr) {
            return -1;
        }
    }

    return val + double_close_rec(x, i-1, file_ptr);
}

#ifndef NO_MAIN
int main() {
    FILE* file = 0;
#ifdef NO_BUG
    printf("%i\n", double_close_rec(10, 20, &file));
    file = fopen("file.txt", "r");
    printf("%i\n", double_close_rec(11, 18, &file));
#else
    printf("%i\n", double_close_rec(11, 20, &file));
#endif

    return 1;
}
#endif

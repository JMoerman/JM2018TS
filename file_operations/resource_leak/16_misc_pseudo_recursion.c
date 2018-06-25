#include <stdio.h>
#include <stdlib.h>
#include "resource_leak.h"

int res_leak_pseudo_rec1(int x, int y, int i, char* file_name) {
    FILE* file;
    FILE** file_ptr;
    int val;
#ifdef CATCH_BAD_PARAM
    if(x >= y && x < 10) {
        return -1;
    }
#endif

    file = fopen(file_name, "r");
    if(!file) {
        return -1;
    }
    file_ptr = &file;
    val = ((int) fgetc(file));

    if(i > 0) {
        fclose(file);
        return 37;
    }

    if(x < y) {
        fclose(file);
        file = 0;
    } else {
        fgetc(file);
    }

    return val + res_leak_pseudo_rec2(x, y, 1, file_ptr, file_name);
}

int res_leak_pseudo_rec2(int x, int y, int i, FILE** file_ptr, char* file_name) {
    int val = 78;
    if(i <= 0) {
        return 5 + res_leak_pseudo_rec1(x, y, 1, file_name);
    }

    if(x < 10) {
        val += 2;
    } else {
        if(*file_ptr) {
            val -= ((int) fgetc(*file_ptr));
            fclose(*file_ptr);
            *file_ptr = 0;
        }
    }
    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    printf("%i\n", res_leak_pseudo_rec1(9, 10, 0, "file.txt"));
    printf("%i\n", res_leak_pseudo_rec1(11, 10, 0, "file.txt"));
#else
    printf("%i\n", res_leak_pseudo_rec1(9, 8, 0, "file.txt"));
#endif

    return 1;
}
#endif

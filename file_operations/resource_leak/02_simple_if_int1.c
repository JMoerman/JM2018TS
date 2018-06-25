#include <stdio.h>
#include <stdlib.h>
#include "resource_leak.h"

void res_leak_if_else_int1(int x, int y) {
    int val = 0;
    FILE* file;

#ifdef CATCH_BAD_PARAM
    if(x > 10 && x < y) {
        return;
    }
#endif

    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    if(x <= 10) {
        val = ((int) fgetc(file));
        fclose(file);
    } else {
        val = ((int) fgetc(file))*2;
    }

    if(x >= y) {
        if(x > 10) {
            val = ((int) fgetc(file)) * 2;
            fclose(file);
        }
    } else {
        val += 10;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_if_else_int1(10, 10);
    res_leak_if_else_int1(10, 11);
    res_leak_if_else_int1(11, 11);
#else
    res_leak_if_else_int1(10, 10); /* OK */
    res_leak_if_else_int1(11, 12); /* DANGER */
    res_leak_if_else_int1(11, 11); /* OK */
#endif

    return 1;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include "resource_leak.h"

void res_leak_if_else_int2(int x, int y) {
    FILE* file;
    int val = 0;
    int m, n;

    m = -1;
    n = 5;

    x = x*m+n;

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
    res_leak_if_else_int2(-5, 10);
    res_leak_if_else_int2(-5, 11);
    res_leak_if_else_int2(-6, 11);
#else
    res_leak_if_else_int2(-5, 10); /* OK */
    res_leak_if_else_int2(-6, 12); /* DANGER */
    res_leak_if_else_int2(-6, 11); /* OK */
#endif

    return 1;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include "access_closed.h"

void access_closed_if_else_int1(int x, int y) {
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
        val = ((int) fgetc(file)) * 2;
    } else {
        val = (int) fgetc(file);
        fclose(file);
    }

    if(x >= y) {
        val += 10;
    } else {
        val = ((int) fgetc(file)) * 2;
    }

    if(x <= 10) {
        fclose(file);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_if_else_int1(10, 10);
    access_closed_if_else_int1(10, 11);
    access_closed_if_else_int1(11, 11);
#else
    access_closed_if_else_int1(10, 10); /* OK */
    access_closed_if_else_int1(11, 12); /* DANGER */
    access_closed_if_else_int1(11, 11); /* OK */
#endif

    return 1;
}
#endif

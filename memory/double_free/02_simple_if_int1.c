#include <stdio.h>
#include <stdlib.h>
#include "double_free.h"

void double_free_if_else_int1(int x, int y) {
    int* data;

#ifdef CATCH_BAD_PARAM
    if(x > 10 && x < y) {
        return;
    }
#endif

    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    if(x > 10) {
        free(data);
    } else {
        data[3] = -4;
    }

    if(x < y) {
        free(data); /* DANGER, if x <= 10 & x >= y */
    }

    if(x <= 10 && x >= y) {
        free(data);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_if_else_int1(10, 10);
    double_free_if_else_int1(10, 11);
    double_free_if_else_int1(11, 11);
#else
    double_free_if_else_int1(10, 10); /* OK */
    double_free_if_else_int1(11, 12); /* DANGER */
    double_free_if_else_int1(11, 11); /* OK */
#endif

    return 1;
}
#endif

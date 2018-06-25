#include <stdio.h>
#include <stdlib.h>
#include "double_free.h"

void double_free_goto(int x) {
    int* data;
    int i = 0;

    if(x <= 0) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

GOTO_LABEL:
    if(i <= x) {
        free(data);
    } else {
        printf("Data is freed\n");
    }

    if(i == 0) {
        i++;
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_goto(0);
#else
    double_free_goto(1);
#endif

    return 1;
}
#endif

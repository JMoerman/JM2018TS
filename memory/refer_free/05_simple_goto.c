#include <stdio.h>
#include <stdlib.h>
#include "refer_free.h"

void refer_free_goto(int x) {
    int* data;
    int val;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    *data = 7698;

GOTO_LABEL:
    if(i <= x) {
        val = *data;
    } else {
        printf("%i\n", val);
    }

    if(i == 0) {
        i++;
        free(data);
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_goto(0);
#else
    refer_free_goto(1);
#endif

    return 1;
}
#endif

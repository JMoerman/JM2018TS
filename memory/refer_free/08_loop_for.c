#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "refer_free.h"

void refer_free_for(int x) {
    int* data;
    int val = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    *data = 9;

    free(data);

    for(i = 0; i < 20; i++) {
        if(i > x) {
            val += *data;
        } else {
            val += 37;
        }
        if(i == 10) {
            data = malloc(5*sizeof(int));
            if(!data) {
                return;
            }
            *data = 9;
        }
    }

    free(data);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_for(10);
#else
    refer_free_for(9);
#endif

    return 1;
}
#endif

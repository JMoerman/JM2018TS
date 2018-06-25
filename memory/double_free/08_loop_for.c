#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "double_free.h"

void double_free_for(int x) {
    int* data;
    bool is_freed;
    int n_freed = 21;
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

    free(data);
    is_freed = true;

    for(i = 0; i < 20; i++) {
        if(i > x && is_freed) { /* should be !is_freed */
            free(data); /* DANGER: x < 10 */
            data = malloc(5*sizeof(int));
            if(!data) {
                return;
            }
            is_freed = false;
        } else {
            n_freed--;
        }
        if(i == 10) {
            data = malloc(5*sizeof(int));
            if(!data) {
                return;
            }
            is_freed = false;
        }
    }

    if(!is_freed) {
        free(data);
        n_freed--;
    }

    printf("Times freed = %i", n_freed);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_for(10);
#else
    double_free_for(9);
#endif

    return 1;
}
#endif

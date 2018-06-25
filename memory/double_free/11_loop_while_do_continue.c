#include <stdio.h>
#include <stdlib.h>
#include "double_free.h"

void double_free_do_while_continue(int x) {
    int* data;
    bool is_freed;
    int n_freed = 30;
    int i = 0;
    printf("Times freed = %i\n", n_freed);
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

    do {
        if(i == 8) {
            i++;
            continue;
        }
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
        i++;
    } while(i < 30);

    if(!is_freed) {
        free(data);
        n_freed--;
    }

    printf("Times freed = %i\n", n_freed);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_do_while_continue(10);
#else
    double_free_do_while_continue(9);
#endif

    return 1;
}
#endif

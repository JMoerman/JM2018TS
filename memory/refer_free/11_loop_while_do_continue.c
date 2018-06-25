#include <stdio.h>
#include <stdlib.h>
#include "refer_free.h"

void refer_free_do_while_continue(int x) {
    int* data;
    int val = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10 && x != 8) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    free(data);

    do {
        if(i == 8) {
            i++;
            continue;
        }
        if(i > x) {
            val += *data; /* Dangerous if x < 10 */
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
        i++;
    } while(i < 30);

    free(data);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_do_while_continue(10);
#else
    refer_free_do_while_continue(9);
#endif

    return 1;
}
#endif

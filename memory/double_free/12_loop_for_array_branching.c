#include <stdio.h>
#include <stdlib.h>
#include "double_free.h"

void double_free_for_array(int x) {
    int* data;
    int p[20];
    int val = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x != 19) {
        return;
    }
#endif

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    *data = 27;

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            val = *data;
            free(data);
        } else {
            free(data); /* DANGER: x < 19 */
            data = malloc(sizeof(int));
            if(!data) {
                break;
            }
            *data = i;
        }
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_for_array(19);
#else
    double_free_for_array(10);
#endif

    return 1;
}
#endif

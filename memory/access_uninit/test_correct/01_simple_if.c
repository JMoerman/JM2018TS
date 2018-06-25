#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uninitialized_malloc.h"

void uninit_malloc_if_else(bool a, bool b) {
    int* data;
    int val;


    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    if(a) {
        *data = 1;
    }

    if(b) {
        val = 37 * 2;
    } else {
        val = 11 * *data; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);

    free(data);
}

int main() {
    uninit_malloc_if_else(true, true);
    uninit_malloc_if_else(true, false);
    uninit_malloc_if_else(false, true);

    return 1;
}

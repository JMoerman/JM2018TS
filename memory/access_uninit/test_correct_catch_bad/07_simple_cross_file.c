#include "uninitialized_malloc.h"
#include "common.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void uninit_malloc_cross_file(bool a, bool b) {
    int* data;
    int val;
    int* int_ptr;

    if(!a & !b) {
        return;
    }

    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    int_ptr = (int*) choose_pointer((void*) data, (void*) &val, a);
    *int_ptr = 768;

    if(b) {
        val = 10 * 2;
    } else {
        val = 10 * *data; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
    free(data);
}

int main() {
    uninit_malloc_cross_file(true, true);
    uninit_malloc_cross_file(true, false);
    uninit_malloc_cross_file(false, true);
    return 1;
}

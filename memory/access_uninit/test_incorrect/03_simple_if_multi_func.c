#include "uninitialized_malloc.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void possibly_assign(int* dest, int val, bool condition) {
    if(condition) {
        *dest = val;
    }
}

static int conditional_assign(int* ptr1, int* ptr2, bool condition) {
    if(condition) {
        return *ptr1;
    }
    return *ptr2;
}

void uninit_malloc_if_else_multi(bool a, bool b) {
    int* data;
    int val = -7189;


    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    possibly_assign(data, 37, a);

    val = conditional_assign(&val, data, b); /* DANGER, if !a & !b */

    printf("%i\n", val);

    free(data);
}

int main() {
    uninit_malloc_if_else_multi(true, true); /* OK */
    uninit_malloc_if_else_multi(false, false); /* DANGER */
    uninit_malloc_if_else_multi(false, true); /* OK */
    return 1;
}

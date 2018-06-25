#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uninitialized_malloc.h"

static void possibly_assign(int** dest, int val, bool condition) {
    if(condition) {
        **dest = val;
    }
}

void uninit_malloc_function_pointer(bool a, bool b, void (*f)(int**, int, bool)) {
    int *data;


    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    (*f)(&data, 5, a);
    (*f)(&data, 13, b);

    printf("%i\n", *data);

    free(data);
}

int main() {
    uninit_malloc_function_pointer(true, true, &possibly_assign); /* OK */
    uninit_malloc_function_pointer(false, false, &possibly_assign); /* DANGER */
    uninit_malloc_function_pointer(false, true, &possibly_assign); /* OK */

    return 1;
}

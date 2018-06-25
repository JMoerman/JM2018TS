#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "refer_free.h"

static void assign_possibly_freed(int** dest, bool free_data) {
    int* data = malloc(5*sizeof(int));
    *dest = data;
    if(!data) {
        return;
    }
    if(free_data) {
        free(data);
    } else {
        *data = 67982;
    }
}

void refer_free_function_pointer(bool a, bool b, void (*f)(int** dest, bool free_data)) {
    int* data;
    int val = 89;

#ifdef CATCH_BAD_PARAM
    if(!f || (!a & !b)) {
        return;
    }
#endif

    (*f)(&data, !a);

    if(!b && data) {
        val = *data; /* DANGER, if !a & !b */
    }

    if(a && data) {
        free(data);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_function_pointer(true, true, &assign_possibly_freed);
    refer_free_function_pointer(true, false, &assign_possibly_freed);
    refer_free_function_pointer(false, true, &assign_possibly_freed);
#else
    refer_free_function_pointer(true, true, &assign_possibly_freed); /* OK */
    refer_free_function_pointer(false, false, &assign_possibly_freed); /* DANGER */
    refer_free_function_pointer(false, true, &assign_possibly_freed); /* OK */
#endif

    return 1;
}
#endif

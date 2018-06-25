#include "memory_leak.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void local_conditional_free(int** ptr, bool condition) {
    if(condition) {
        free(*ptr);
    }
}

static int conditional_dereference(int** ptr, int def, bool condition) {
    if(condition) {
        return **ptr;
    }
    return def;
}

void mem_leak_if_else_multi(bool a, bool b) {
    int val;
    int* data;
    int** data_ptr = &data;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    *data = 27;

    local_conditional_free(data_ptr, a);
    val = conditional_dereference(data_ptr, 897, !a);
    local_conditional_free(data_ptr, b & !a);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_if_else_multi(true, true);
    mem_leak_if_else_multi(true, false);
    mem_leak_if_else_multi(false, true);
#else
    mem_leak_if_else_multi(true, true); /* OK */
    mem_leak_if_else_multi(false, false); /* DANGER */
    mem_leak_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif

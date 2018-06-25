#include "double_free.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void local_conditional_free(int** ptr, bool condition) {
    if(condition) {
        free(*ptr);
    }
}

void double_free_if_else_multi(bool a, bool b) {
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

    local_conditional_free(data_ptr, a & b);
    local_conditional_free(data_ptr, !b);
    local_conditional_free(data_ptr, !a); /* DANGER, if !a & !b */
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_if_else_multi(true, true);
    double_free_if_else_multi(true, false);
    double_free_if_else_multi(false, true);
#else
    double_free_if_else_multi(true, true); /* OK */
    double_free_if_else_multi(false, false); /* DANGER */
    double_free_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif

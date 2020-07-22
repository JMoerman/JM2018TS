#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "double_free.h"

int double_free_rec_decr_alt(int x, int i, int** data_ptr, bool* is_freed) {
    if(i <= 1) {
        return 0;
    }

    return double_free_rec_multi_alt(x, i-1, data_ptr, is_freed);
}

int double_free_rec_multi_alt(int x, int i, int** data_ptr, bool* is_freed) {
    int n_freed = 0;

    if(i <= 1) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(x < 9 && i >= 10) {
        return -1;
    }
#endif

    if(i < 20 && i > x) {
        free(*data_ptr); /* DANGER: x < 9 */
        *data_ptr = malloc(5*sizeof(int));
        if(!data_ptr) {
            *is_freed = true;
            return 0;
        }
        *is_freed = false;
    } else {
        n_freed--;
    }
    if(i == 10 && !*is_freed) {
        free(*data_ptr);
        *is_freed = true;
        n_freed++;
    }

    return 1 + n_freed + double_free_rec_decr_alt(x, i, data_ptr, is_freed);
}

#ifndef NO_MAIN
int main() {
    int* data = malloc(sizeof(int));
    bool is_freed = false;
    if(!data) {
        return 0;
    }
#ifdef NO_BUG
    printf("%i\n", double_free_rec_multi_alt(9, 20, &data, &is_freed));
#else
    printf("%i\n", double_free_rec_multi_alt(8, 20, &data, &is_freed));
#endif
    if(!is_freed) {
        free(data);
        is_freed = true;
    }

    return 1;
}
#endif

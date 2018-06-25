#include <stdio.h>
#include <stdbool.h>
#include "uninit_ptr.h"

static void local_assign_pointer(int*** dest, int** source1, int** source2, bool condition) {
    if(condition) {
        *dest = source1;
    } else {
        *dest = source2;
    }
}

void uninit_ptr_function_pointer(bool a, bool b, void (*f)(int***, int**, int**, bool)) {
    int arr[3] = {1, 2, 3};
    int* arr_allias = arr;
    int* uninit;
    int** ptr;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!f || (!a & !b)) {
        return;
    }
#endif

    (*f)(&ptr, &arr_allias, &uninit, a);

    if(b) {
        val = arr[2];
    } else {
        val = **ptr; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_ptr_function_pointer(true, true, &local_assign_pointer);
    uninit_ptr_function_pointer(true, false, &local_assign_pointer);
    uninit_ptr_function_pointer(false, true, &local_assign_pointer);
#else
    uninit_ptr_function_pointer(true, true, &local_assign_pointer); /* OK */
    uninit_ptr_function_pointer(false, false, &local_assign_pointer); /* DANGER */
    uninit_ptr_function_pointer(false, true, &local_assign_pointer); /* OK */
#endif

    return 1;
}
#endif

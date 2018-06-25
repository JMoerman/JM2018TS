#include <stdio.h>
#include <stdbool.h>
#include "nullpointer.h"

static void local_assign_pointer(void** dest, void* source1, void* source2, bool condition) {
    if(condition) {
        *dest = source1;
    } else {
        *dest = source2;
    }
}

void nullpointer_function_pointer(bool a, bool b, void (*f)(void**, void*, void*, bool)) {
    int arr[3] = {1, 2, 3};
    int* ptr;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!f || (!a & !b)) {
        return;
    }
#endif

    (*f)((void**) &ptr, (void*) arr, 0, a);

    if(b) {
        val = arr[2];
    } else {
        val = ptr[2]; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_function_pointer(true, true, &local_assign_pointer);
    nullpointer_function_pointer(true, false, &local_assign_pointer);
    nullpointer_function_pointer(false, true, &local_assign_pointer);
#else
    nullpointer_function_pointer(true, true, &local_assign_pointer); /* OK */
    nullpointer_function_pointer(false, false, &local_assign_pointer); /* DANGER */
    nullpointer_function_pointer(false, true, &local_assign_pointer); /* OK */
#endif

    return 1;
}
#endif

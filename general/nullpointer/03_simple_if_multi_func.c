#include "nullpointer.h"
#include <stdbool.h>
#include <stdio.h>

static int* choose_pointer_local(int* source1, int* source2, bool condition) {
    if(condition) {
        return source1;
    } else {
        return source2;
    }
}

static int int_dereference_choice_local(int* source1, int* source2, bool condition) {
    if(condition) {
        return *source1;
    }
    return *source2;
}

void nullpointer_if_else_multi(bool a, bool b) {
    int arr[3] = {1, 2, 3};
    int* ptr = 0;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    ptr = choose_pointer_local(arr+1, 0, a);

    val = int_dereference_choice_local(arr+2, ptr, b); /* DANGER, if !a & !b */

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_if_else_multi(true, true);
    nullpointer_if_else_multi(true, false);
    nullpointer_if_else_multi(false, true);
#else
    nullpointer_if_else_multi(true, true); /* OK */
    nullpointer_if_else_multi(false, false); /* DANGER */
    nullpointer_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif

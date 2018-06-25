#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "resource_leak.h"

static int assign_possibly_closed(FILE** dest, bool close_file) {
    int val;
    FILE* file = fopen("file.txt","r");
    *dest = file;
    if(!file) {
        return -1;
    }
    val = (int) fgetc(file);
    if(close_file) {
        fclose(file);
    }
    return val;
}

void res_leak_function_pointer(bool a, bool b, int (*f)(FILE** dest, bool close_file)) {
    FILE* file;
    int val = 0;

#ifdef CATCH_BAD_PARAM
    if(!f || (!a & !b)) {
        return;
    }
#endif

    val = (*f)(&file, a);

    if(b && !a && file) {
        val += (int) fgetc(file);
        fclose(file);
    } else {
        val += 687;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_function_pointer(true, true, &assign_possibly_closed);
    res_leak_function_pointer(true, false, &assign_possibly_closed);
    res_leak_function_pointer(false, true, &assign_possibly_closed);
#else
    res_leak_function_pointer(true, true, &assign_possibly_closed); /* OK */
    res_leak_function_pointer(false, false, &assign_possibly_closed); /* DANGER */
    res_leak_function_pointer(false, true, &assign_possibly_closed); /* OK */
#endif

    return 1;
}
#endif

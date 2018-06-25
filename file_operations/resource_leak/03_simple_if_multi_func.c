#include "resource_leak.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void local_conditional_close(FILE** ptr, bool condition) {
    if(condition) {
        fclose(*ptr);
    }
}

static int conditional_fgetc(FILE** ptr, int def, bool condition) {
    if(condition) {
        return fgetc(*ptr);
    }
    return def;
}

void res_leak_if_else_multi(bool a, bool b) {
    int val;
    FILE* file;
    FILE** file_ptr = &file;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif
    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    local_conditional_close(file_ptr, a);
    val = conditional_fgetc(file_ptr, 897, !a);
    local_conditional_close(file_ptr, b & !a);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_if_else_multi(true, true);
    res_leak_if_else_multi(true, false);
    res_leak_if_else_multi(false, true);
#else
    res_leak_if_else_multi(true, true); /* OK */
    res_leak_if_else_multi(false, false); /* DANGER */
    res_leak_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif

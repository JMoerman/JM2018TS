#include "access_closed.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef s_FILES_AC_REFCOUNT
#define s_FILES_AC_REFCOUNT
void access_closed_cont_init(FileCont* cont) {
    cont->refc = 1;
    cont->file = 0;
}

FileCont* access_closed_cont_new() {
    FileCont* new_cont;

    new_cont = malloc(sizeof(FileCont));

    if(new_cont) {
        access_closed_cont_init(new_cont);
    }
    return new_cont;
}

void access_closed_cont_ref(FileCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void access_closed_cont_unref(FileCont* cont) {
    if(cont->refc <= 1) {
        if(cont->file) fclose(cont->file);
    } else {
        cont->refc--;
    }
}

FILE* access_closed_cont_get_file(FileCont* cont) {
    return cont->file;
}
void access_closed_cont_set_file(FileCont* cont, FILE* file) {
    cont->file = file;
}
#endif //s_FILES_AC_REFCOUNT

#ifndef NO_MAIN
int main() {
    FileCont* cont;
    FILE* file;
    int val;

    file = fopen("file.txt", "r");
    if(!file) {
        return -1;
    }

    cont = access_closed_cont_new();
    if(!cont) {
        fclose(file);
        return 1;
    }
    access_closed_cont_set_file(cont, file);

    access_closed_cont_ref(cont);
    access_closed_cont_ref(cont);
    access_closed_cont_unref(cont);
    access_closed_cont_unref(cont);
#ifdef NO_BUG
    val = ((int) fgetc(access_closed_cont_get_file(cont)));
    access_closed_cont_unref(cont);
#else
    access_closed_cont_unref(cont);
    val = ((int) fgetc(access_closed_cont_get_file(cont)));
#endif
    free(cont);

    printf("%i\n", val);

    return 1;
}
#endif

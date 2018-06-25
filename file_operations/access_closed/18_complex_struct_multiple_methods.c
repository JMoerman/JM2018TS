#include <stdio.h>
#include <stdlib.h>
#include "access_closed.h"

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
        fclose(cont->file);
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

void access_closed_struct(int x, int y) {
    FileCont cont;
    FILE* file;
    int val = 78;

#ifdef CATCH_BAD_PARAM
    if(x > 10 && x <= y) {
        return;
    }
#endif

    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    access_closed_cont_init(&cont);
    access_closed_cont_set_file(&cont, file);

    if(x <= y) {
        fclose(access_closed_cont_get_file(&cont));
    }

    if(x > 10) {
        val = (int) fgetc(file);
    } else {
        val = val * 2;
    }

    if(x > y) {
        fclose(access_closed_cont_get_file(&cont));
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_struct(9, 10);
    access_closed_struct(10, 11);
    access_closed_struct(11, 10);
#else
    access_closed_struct(11, 11); /* DANGER */
#endif

    return 1;
}
#endif

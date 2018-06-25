#include <stdio.h>
#include <stdlib.h>
#include "resource_leak.h"

#ifndef s_FILES_RL_REFCOUNT
#define s_FILES_RL_REFCOUNT
void res_leak_cont_init(FileCont* cont) {
    cont->refc = 1;
    cont->file = 0;
}

FileCont* res_leak_cont_new() {
    FileCont* new_cont;

    new_cont = malloc(sizeof(FileCont));

    if(new_cont) {
        res_leak_cont_init(new_cont);
    }
    return new_cont;
}

void res_leak_cont_ref(FileCont* cont) {
    if(cont) {
        cont->refc++;
    }
}
void res_leak_cont_unref(FileCont* cont) {
    if(cont->refc <= 1) {
        fclose(cont->file);
    } else {
        cont->refc--;
    }
}

FILE* res_leak_cont_get_file(FileCont* cont) {
    return cont->file;
}
void res_leak_cont_set_file(FileCont* cont, FILE* file) {
    cont->file = file;
}
#endif //s_FILES_RL_REFCOUNT

void res_leak_struct(int x, int y) {
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

    res_leak_cont_init(&cont);
    res_leak_cont_set_file(&cont, file);

    if(x > y) {
        fclose(file);
        file = 0;
    }

    if(x <= 10) {
        if(file) {
            val = (int) fgetc(file);
            fclose(res_leak_cont_get_file(&cont));
        }
    } else {
        val = val * 2;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_struct(9, 10);
    res_leak_struct(10, 11);
    res_leak_struct(11, 10);
#else
    res_leak_struct(11, 11); /* DANGER */
#endif

    return 1;
}
#endif

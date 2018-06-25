#include "resource_leak.h"
#include <stdlib.h>
#include <stdio.h>

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
        if(cont->file) fclose(cont->file);
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

#ifndef NO_MAIN
int main() {
    FileCont* cont;
    FILE* file;
    int val;

    file = fopen("file.txt", "r");
    if(!file) {
        return -1;
    }

    cont = res_leak_cont_new();
    if(!cont) {
        fclose(file);
        return 1;
    }
    res_leak_cont_set_file(cont, file);

    res_leak_cont_ref(cont);
    res_leak_cont_ref(cont);
    res_leak_cont_unref(cont);
    res_leak_cont_unref(cont);
    val = ((int) fgetc(res_leak_cont_get_file(cont)));
#ifdef NO_BUG
    res_leak_cont_unref(cont);
#endif
    free(cont);

    printf("%i\n", val);

    return 1;
}
#endif

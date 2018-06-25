#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_copy.h"

static char long_string[22] = "";
static char short_string[13] = "";

#ifndef s_NULLPOINTER_REFCOUNT
#define s_NULLPOINTER_REFCOUNT
static char small_string[15] = "";

void string_copy_cont_init(StringCont* cont) {
    cont->counter = 1;
    cont->small_string = small_string;
    cont->normal_string = 0;
    cont->selected_string = &(cont->normal_string);
}

StringCont* string_copy_cont_new() {
    StringCont* new_cont;

    new_cont = malloc(sizeof(StringCont));

    if(new_cont) {
        string_copy_cont_init(new_cont);
    }
    return new_cont;
}

void string_copy_cont_incr(StringCont* cont) {
    if(cont) {
        cont->counter++;
    }
}
void string_copy_cont_decr(StringCont* cont) {
    if(cont->counter <= 1) {
        cont->selected_string = &(cont->small_string);
    } else {
        cont->counter--;
    }
}

char* string_copy_cont_get_string(StringCont* cont) {
    return *(cont->selected_string);
}
void string_copy_cont_set_string(StringCont* cont, char* string) {
    cont->normal_string = string;
}
#endif //s_NULLPOINTER_REFCOUNT

void string_copy_struct(int x, int y) {
    StringCont cont;
    char* to_print;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif
    string_copy_cont_init(&cont);

    string_copy_cont_set_string(&cont, short_string);

    if(x < y) {
        string_copy_cont_set_string(&cont, long_string);
    }

    to_print = string_copy_cont_get_string(&cont);

    if(x > 10) {
        strcpy(to_print, "short string");
    } else {
        /* DANGER: if x <= 10 & x >= y */
        strcpy(to_print, "this is a long string");
    }

    printf("%s\n", string_copy_cont_get_string(&cont));
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_copy_struct(9, 10);
    string_copy_struct(10, 11);
    string_copy_struct(11, 10);
#else
    string_copy_struct(10, 10); /* DANGER */
#endif

    return 1;
}
#endif

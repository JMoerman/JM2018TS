#include "string_copy.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char long_string[22] = "";

#ifndef s_STRINGS_UC_REFCOUNT
#define s_STRINGS_UC_REFCOUNT
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
        cont->selected_string = (char**) &(cont->small_string);
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
#endif //s_STRINGS_UC_REFCOUNT

#ifndef NO_MAIN
int main() {
    StringCont* cont;

    cont = string_copy_cont_new();
    if(!cont) {
        return 1;
    }
    string_copy_cont_set_string(cont, long_string);

    string_copy_cont_incr(cont);
    string_copy_cont_incr(cont);
    string_copy_cont_decr(cont);
    string_copy_cont_decr(cont);
#ifndef NO_BUG
    string_copy_cont_decr(cont);
#endif

    strcpy(string_copy_cont_get_string(cont), "this is a long string");

    printf("%s\n", string_copy_cont_get_string(cont));

    free(cont);

    return 1;
}
#endif

#include "integer_overflow.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef s_INTEGERS_O_REFCOUNT
#define s_INTEGERS_O_REFCOUNT
void integer_overflow_cont_init(IntCont* cont) {
    cont->counter = 1;
    cont->int_value = 0;
}

IntCont* integer_overflow_cont_new() {
    IntCont* new_cont;

    new_cont = malloc(sizeof(IntCont));

    if(new_cont) {
        integer_overflow_cont_init(new_cont);
    }
    return new_cont;
}

void integer_overflow_cont_incr(IntCont* cont) {
    if(cont) {
        cont->counter++;
    }
}
void integer_overflow_cont_decr(IntCont* cont) {
    if(cont->counter <= 1) {
        cont->int_value = INT_MAX;
    } else {
        cont->counter--;
    }
}

int integer_overflow_cont_get_int(IntCont* cont) {
    return cont->int_value;
}
void integer_overflow_cont_set_int(IntCont* cont, int int_value) {
    cont->int_value = int_value;
}
#endif //s_INTEGERS_O_REFCOUNT

#ifndef NO_MAIN
int main() {
    IntCont* cont;

    cont = integer_overflow_cont_new();
    if(!cont) {
        return 1;
    }
    integer_overflow_cont_set_int(cont, 35);

    integer_overflow_cont_incr(cont);
    integer_overflow_cont_incr(cont);
    integer_overflow_cont_decr(cont);
    integer_overflow_cont_decr(cont);
#ifndef NO_BUG
    integer_overflow_cont_decr(cont);
#endif

    printf("%i\n", integer_overflow_cont_get_int(cont) + 512);

    free(cont);

    return 1;
}
#endif

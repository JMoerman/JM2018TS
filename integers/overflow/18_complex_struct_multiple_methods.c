#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "integer_overflow.h"

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

void integer_overflow_struct(int x, int y) {
    IntCont cont;
    int val;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif
    integer_overflow_cont_init(&cont);

    integer_overflow_cont_set_int(&cont, INT_MAX - 300);

    if(x < y) {
        integer_overflow_cont_set_int(&cont, INT_MAX - 500);
    }

    if(x > 10) {
        val = integer_overflow_cont_get_int(&cont) + 200;
    } else {
        /* DANGER: if x <= 10 & x >= y */
        val = integer_overflow_cont_get_int(&cont) + 400;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_struct(9, 10);
    integer_overflow_struct(10, 11);
    integer_overflow_struct(11, 10);
#else
    integer_overflow_struct(10, 10); /* DANGER */
#endif

    return 1;
}
#endif

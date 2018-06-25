#include <stdio.h>
#include <stdlib.h>
#include "divide_by_zero.h"

#ifndef s_DIVBYZERO_REFCOUNT
#define s_DIVBYZERO_REFCOUNT
DivideCont* divide_zero_cont_new() {
    DivideCont* new_cont;

    new_cont = malloc(sizeof(DivideCont));

    if(new_cont) {
        new_cont->counter = 1;
        new_cont->divisor = 0;
    }
    return new_cont;
}

void divide_zero_cont_incr(DivideCont* cont) {
    if(cont) {
        cont->counter++;
    }
}
void divide_zero_cont_decr(DivideCont* cont) {
    if(cont->counter <= 1) {
        cont->divisor = 0;
    } else {
        cont->counter--;
    }
}

int divide_zero_cont_get_divisor(DivideCont* cont) {
    return cont->divisor;
}
void divide_zero_cont_set_divisor(DivideCont* cont, int divisor) {
    cont->divisor = divisor;
}
#endif //s_DIVBYZERO_REFCOUNT

void divide_zero_struct(int x, int y) {
    DivideCont cont;
    int val;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    divide_zero_cont_set_divisor(&cont, 0);

    if(x < y) {
        divide_zero_cont_set_divisor(&cont, 7);
    }

    if(x > 10) {
        val = 50 / 37;
    } else {
        /* DANGER: if x <= 10 & x >= y */
        val = 30 / divide_zero_cont_get_divisor(&cont);
    }

    printf("x=%i: %i\n", x, val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_struct(9, 10);
    divide_zero_struct(10, 11);
    divide_zero_struct(11, 10);
#else
    divide_zero_struct(10, 10); /* DANGER */
#endif

    return 1;
}
#endif

#include "divide_by_zero.h"
#include <stdlib.h>
#include <stdio.h>

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

#ifndef NO_MAIN
int main() {
    DivideCont* cont;
    int val;

    cont = divide_zero_cont_new();
    if(!cont) {
        return 1;
    }
    divide_zero_cont_set_divisor(cont, 35);

    divide_zero_cont_incr(cont);
    divide_zero_cont_incr(cont);
    divide_zero_cont_decr(cont);
    divide_zero_cont_decr(cont);
#ifndef NO_BUG
    divide_zero_cont_decr(cont);
#endif

    val = 30 / divide_zero_cont_get_divisor(cont);

    printf("%i\n", val);

    free(cont);

    return 1;
}
#endif

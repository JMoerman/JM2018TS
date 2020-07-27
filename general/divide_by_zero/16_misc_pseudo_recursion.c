#include <stdio.h>
#include "divide_by_zero.h"

int divide_zero_pseudo_rec1(int x, int y, int i, int div1, int div2) {
#ifdef CATCH_BAD_PARAM
    if(!div2 && x >= y && x < 10) {
        return 0;
    }
    if(!div1 && (x > 10 || (x <= 10 && x < y))) {
        return 0;
    }
#endif

    if(i > 0) {
        return 37;
    }

    if(x < y) {
        div2 = div1;
    }

    return divide_zero_pseudo_rec2(x, y, 1, div1, div2);
}

int divide_zero_pseudo_rec2(int x, int y, int i, int div1, int div2) {
    int divisor;
    if(i <= 0) {
        return 10 / div1 + divide_zero_pseudo_rec1(x, y, 1, div1, div2);
    }

    if(x > 10) {
        divisor = div1;
    } else {
        divisor = div2;
    }

    return 100 / divisor;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    printf("%i\n", divide_zero_pseudo_rec1(9, 10, 0, 5, 0));
    printf("%i\n", divide_zero_pseudo_rec1(10, 10, 0, 5, 6));
    printf("%i\n", divide_zero_pseudo_rec1(11, 10, 0, 5, 0));
#else
    printf("%i\n", divide_zero_pseudo_rec1(10, 10, 0, 5, 0));
#endif

    return 1;
}
#endif

#include <stdio.h>
#include "divide_by_zero.h"

int divide_zero_rec_decr(int x, int i, int div1, int div2) {
    if(i <= 1) {
        return 0;
    }

    return divide_zero_rec_multi(x, i-1, div1, div2);
}

int divide_zero_rec_multi(int x, int i, int div1, int div2) {
    int divisor;

    if(i <= 1 || div1 == 0) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(x > 10 && i < x && div2 == 0) {
        return divide_zero_rec(x, i-1, div1, div1);
    }
#endif

    if(i < x) {
        divisor = div2;
    } else {
        divisor = div1;
    }
    if(i == 10) {
        div2 = div1;
    }
    return divide_zero_rec_decr(x, i, div1, div2) + 100 / divisor;
}



#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    printf("%i", divide_zero_rec_multi(10, 20, 6, 0));
#else
    printf("%i", divide_zero_rec_multi(11, 20, 6, 0));
#endif

    return 1;
}
#endif

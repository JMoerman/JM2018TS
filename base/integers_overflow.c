#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int x;

#ifdef NO_BUG
    x = INT_MAX - 1;
#else
    x = INT_MAX;
#endif

    printf("%i\n", x + 1);

    return 1;
}

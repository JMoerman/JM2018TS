#include <stdio.h>
#include <stdlib.h>

int main() {
    int* data;
    int x;

#ifdef NO_BUG
    x = 1;
#else
    x = 0;
#endif

    data = malloc(x * sizeof(int));

    if(!data) {
        return -1;
    }

    *data = x;

    printf("%i\n", *data);

    free(data);

    return 1;
}

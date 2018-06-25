#include <stdio.h>
#include <stdlib.h>

int main() {
    int* data;
    int x = 33;

    data = malloc(5 * sizeof(int));

    if(!data) {
        return -1;
    }

    *data = x;

#ifdef NO_BUG
    printf("%i\n", *data);
    free(data);
#else
    free(data);
    printf("%i\n", *data);
#endif

    return 1;
}

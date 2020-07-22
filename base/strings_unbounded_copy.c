#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
#ifdef NO_BUG
    char test_string[22];
#else
    char test_string[13];
#endif

    strcpy(test_string, "this is a long string");

    printf("%s\n", test_string);

    return 1;
}

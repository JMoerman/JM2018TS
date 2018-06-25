#include <stdio.h>
#include <stdlib.h>

int main() {
#ifdef NO_BUG
    char test_string[22];
#else
    char test_string[13];
#endif

    strcpy(to_print, "this is a long string");

    printf("%s\n", test_string);

    return 1;
}

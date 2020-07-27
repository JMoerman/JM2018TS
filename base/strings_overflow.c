#include <stdio.h>
#include <stdlib.h>

int main() {
#ifdef NO_BUG
    char test_string[] = "this is a long string";
#else
    char test_string[] = "short string";
#endif

    test_string[13] = '?';

    printf("%s\n", test_string);

    return 1;
}

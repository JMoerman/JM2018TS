#include <stdbool.h>

void assign_pointer(void** dest, void* source1, void* source2, bool condition) {
    if(condition) {
        *dest = source1;
    } else {
        *dest = source2;
    }
}

void* choose_pointer(void* source1, void* source2, bool condition) {
    if(condition) {
        return source1;
    } else {
        return source2;
    }
}

int int_dereference_choice(int* source1, int* source2, bool condition) {
    if(condition) {
        return *source1;
    }
    return *source2;
}

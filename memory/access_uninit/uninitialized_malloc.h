#include <stdbool.h>

typedef struct _MallocIntCont MallocIntCont;

struct _MallocIntCont {
    int* data;
    unsigned int counter;
};

void uninit_malloc_cont_init(MallocIntCont* cont);
MallocIntCont* uninit_malloc_cont_new();
void uninit_malloc_cont_incr(MallocIntCont* cont);
void uninit_malloc_cont_decr(MallocIntCont* cont);
int uninit_malloc_cont_get_value(MallocIntCont* cont);
void uninit_malloc_cont_set_value(MallocIntCont* cont, int value);
void uninint_val_cont_free(MallocIntCont* cont);

void uninit_malloc_for(int x);
void uninit_malloc_for_complex(int x);
void uninit_malloc_while_continue(int x);
void uninit_malloc_do_while_continue(int x);
void uninit_malloc_for_array(int x);
void uninit_malloc_for_pointer(int x);
void uninit_malloc_goto(int x);
void uninit_malloc_if_else(bool a, bool b);
void uninit_malloc_if_else_multi(bool a, bool b);
void uninit_malloc_if_else_int1(int x, int y);
void uninit_malloc_if_else_int2(int x, int y);
void uninit_malloc_pass_by_reference(bool a, bool b);
int uninit_malloc_switch(int x, int y);
int uninit_malloc_rec_multi(int x, int i, int* ptr1, int* ptr2);
int uninit_malloc_rec(int x, int i, int* ptr1, int* ptr2);
int uninit_malloc_pseudo_rec1(int x, int y, int i, int* ptr1, int* ptr2);
int uninit_malloc_pseudo_rec2(int x, int y, int i, int* ptr1, int* ptr2);
void uninit_malloc_struct(int x, int y);
void uninit_malloc_function_pointer(bool a, bool b, void (*f)(int**, int, bool));
void uninit_malloc_cross_file(bool a, bool b);

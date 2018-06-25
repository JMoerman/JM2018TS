#include <stdbool.h>

typedef struct _NullRefCont NRefCont;

struct _NullRefCont {
    void* p_data;
    unsigned int refc;
};

NRefCont* null_ref_cont_new();
void null_ref(NRefCont* cont);
void null_unref(NRefCont* cont);
void* null_ref_cont_get_pointer(NRefCont* cont);
void null_ref_cont_set_pointer(NRefCont* cont, void* p);

void nullpointer_for(int x);
void nullpointer_for_complex(int x);
void nullpointer_while_continue(int x);
void nullpointer_do_while_continue(int x);
void nullpointer_for_array(int x);
void nullpointer_for_pointer(int x);
void nullpointer_goto(int x);
void nullpointer_if_else(bool a, bool b);
void nullpointer_if_else_multi(bool a, bool b);
void nullpointer_if_else_int1(int x, int y);
void nullpointer_if_else_int2(int x, int y);
void nullpointer_pass_by_reference(bool a, bool b);
int nullpointer_switch(int x, int y);
int nullpointer_rec_multi(int x, int i, int* ptr1, int* ptr2);
int nullpointer_rec(int x, int i, int* ptr1, int* ptr2);
int nullpointer_rec_assign(int x, int i, int* ptr1, int* ptr2);
int nullpointer_pseudo_rec1(int x, int y, int i, int* ptr1, int* ptr2);
int nullpointer_pseudo_rec2(int x, int y, int i, int* ptr1, int* ptr2);
void nullpointer_struct(int x, int y);
void nullpointer_function_pointer(bool a, bool b, void (*f)(void**, void*, void*, bool));
void nullpointer_cross_file(bool a, bool b);

#include <stdbool.h>

typedef struct _UninitRefCont URefCont;

struct _UninitRefCont {
    void** data_ptr;
    void* data;
    void* uninit;
    unsigned int refc;
};

void init_uninit_ref_cont(URefCont* cont);
URefCont* uninit_ref_cont_new();
void uninit_ref(URefCont* cont);
void uninit_unref(URefCont* cont);
void* uninit_ref_cont_get_pointer(URefCont* cont);
void uninit_ref_cont_set_pointer(URefCont* cont, void* p);

void uninit_ptr_for(int x);
void uninit_ptr_for_complex(int x);
void uninit_ptr_while_continue(int x);
void uninit_ptr_do_while_continue(int x);
void uninit_ptr_for_array(int x);
void uninit_ptr_for_pointer(int x);
void uninit_ptr_goto(int x);
void uninit_ptr_if_else(bool a, bool b);
void uninit_ptr_if_else_multi(bool a, bool b);
void uninit_ptr_if_else_int1(int x, int y);
void uninit_ptr_if_else_int2(int x, int y);
void uninit_ptr_pass_by_reference(bool a, bool b);
int uninit_ptr_switch(int x, int y);
int uninit_ptr_rec_multi(int x, int i, int** ptr1, int** ptr2);
int uninit_ptr_rec(int x, int i, int** ptr1, int** ptr2);
int uninit_ptr_rec_assign(int x, int i, int* ptr1, int* ptr2);
int uninit_ptr_pseudo_rec1(int x, int y, int i, int** ptr1, int** ptr2);
int uninit_ptr_pseudo_rec2(int x, int y, int i, int** ptr1, int** ptr2);
void uninit_ptr_struct(int x, int y);
void uninit_ptr_function_pointer(bool a, bool b, void (*f)(int***, int**, int**, bool));
void uninit_ptr_cross_file(bool a, bool b);

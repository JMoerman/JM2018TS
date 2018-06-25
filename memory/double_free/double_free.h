#include <stdbool.h>

typedef struct _DoubleFreeRefCont DRefCont;

struct _DoubleFreeRefCont {
    void* data;
    unsigned int refc;
};

void double_free_cont_init(DRefCont* cont);
DRefCont* double_free_cont_new();
void double_free_cont_ref(DRefCont* cont);
void double_free_cont_unref(DRefCont* cont);
void* double_free_cont_get_pointer(DRefCont* cont);
void double_free_cont_set_pointer(DRefCont* cont, void* p);

void double_free_for(int x);
void double_free_for_complex(int x);
void double_free_while_continue(int x);
void double_free_do_while_continue(int x);
void double_free_for_array(int x);
void double_free_for_pointer(int x);
void double_free_goto(int x);
void double_free_if_else(bool a, bool b);
void double_free_if_else_multi(bool a, bool b);
void double_free_if_else_int1(int x, int y);
void double_free_if_else_int2(int x, int y);
void double_free_pass_by_reference(bool a, bool b);
void double_free_switch(int x, int y);
int double_free_rec_multi(int x, int i, int** data_ptr, bool* is_freed);
int double_free_rec_multi_alt(int x, int i, int** data_ptr, bool* is_freed);
int double_free_rec(int x, int i, int** data_ptr, bool* is_freed);
int double_free_rec_alt(int x, int i, int** data_ptr, bool* is_freed);
int double_free_pseudo_rec1(int x, int y, int i, int** data_ptr);
int double_free_pseudo_rec2(int x, int y, int i, int** data_ptr);
void double_free_struct(int x, int y);
void double_free_function_pointer(bool a, bool b, void (*f)(int** dest, bool free_data));
void double_free_cross_file(bool a, bool b);

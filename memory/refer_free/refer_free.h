#include <stdbool.h>

typedef struct _ReferFreeRefCont RRefCont;

struct _ReferFreeRefCont {
    void* data;
    unsigned int refc;
};

void refer_free_cont_init(RRefCont* cont);
RRefCont* refer_free_cont_new();
void refer_free_cont_ref(RRefCont* cont);
void refer_free_cont_unref(RRefCont* cont);
void* refer_free_cont_get_pointer(RRefCont* cont);
void refer_free_cont_set_pointer(RRefCont* cont, void* p);

void refer_free_for(int x);
void refer_free_for_complex(int x);
void refer_free_while_continue(int x);
void refer_free_do_while_continue(int x);
void refer_free_for_array(int x);
void refer_free_for_pointer(int x);
void refer_free_goto(int x);
void refer_free_if_else(bool a, bool b);
void refer_free_if_else_multi(bool a, bool b);
void refer_free_if_else_int1(int x, int y);
void refer_free_if_else_int2(int x, int y);
void refer_free_pass_by_reference(bool a, bool b);
int refer_free_switch(int x, int y);
int refer_free_rec_multi(int x, int i, int** data_ptr);
int refer_free_rec(int x, int i, int** data_ptr);
int refer_free_pseudo_rec1(int x, int y, int i, int** data_ptr);
int refer_free_pseudo_rec2(int x, int y, int i, int** data_ptr);
void refer_free_struct(int x, int y);
void refer_free_function_pointer(bool a, bool b, void (*f)(int** dest, bool free_data));
void refer_free_cross_file(bool a, bool b);

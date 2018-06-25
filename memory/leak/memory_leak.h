#include <stdbool.h>

typedef struct _MemLeakRefCont LRefCont;

struct _MemLeakRefCont {
    void* data;
    unsigned int refc;
};

void mem_leak_cont_init(LRefCont* cont);
LRefCont* mem_leak_cont_new();
void mem_leak_cont_ref(LRefCont* cont);
void mem_leak_cont_unref(LRefCont* cont);
void* mem_leak_cont_get_pointer(LRefCont* cont);
void mem_leak_cont_set_pointer(LRefCont* cont, void* p);

void mem_leak_for(int x);
void mem_leak_for_complex(int x);
void mem_leak_while_continue(int x);
void mem_leak_do_while_continue(int x);
void mem_leak_for_array(int x);
void mem_leak_for_pointer(int x);
void mem_leak_goto(int x);
void mem_leak_if_else(bool a, bool b);
void mem_leak_if_else_multi(bool a, bool b);
void mem_leak_if_else_int1(int x, int y);
void mem_leak_if_else_int2(int x, int y);
void mem_leak_pass_by_reference(bool a, bool b);
int mem_leak_switch(int x, int y);
int mem_leak_rec_multi(int x, int i, int* data_ptr, bool do_free);
int mem_leak_rec(int x, int i, int* data_ptr, bool do_free);
int mem_leak_pseudo_rec1(int x, int y, int i, int** data_ptr);
int mem_leak_pseudo_rec2(int x, int y, int i, int** data_ptr);
void mem_leak_struct(int x, int y);
void mem_leak_function_pointer(bool a, bool b, void (*f)(int** dest, bool free_data));
void mem_leak_cross_file(bool a, bool b);

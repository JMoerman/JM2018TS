#include <stdbool.h>
#include <stddef.h>

typedef struct _SizeRefCont SizeCont;

struct _SizeRefCont {
    size_t size;
    unsigned int refc;
};

void zero_alloc_cont_init(SizeCont* cont);
SizeCont* zero_alloc_cont_new();
void zero_alloc_cont_ref(SizeCont* cont);
void zero_alloc_cont_unref(SizeCont* cont);
size_t zero_alloc_cont_get_size(SizeCont* cont);
void zero_alloc_cont_set_size(SizeCont* cont, size_t size);

void zero_alloc_for(int x);
void zero_alloc_for_complex(int x);
void zero_alloc_while_continue(int x);
void zero_alloc_do_while_continue(int x);
void zero_alloc_for_array(int x);
void zero_alloc_for_pointer(int x);
void zero_alloc_goto(int x);
void zero_alloc_if_else(bool a, bool b);
void zero_alloc_if_else_multi(bool a, bool b);
void zero_alloc_if_else_int1(int x, int y);
void zero_alloc_if_else_int2(int x, int y);
void zero_alloc_pass_by_reference(bool a, bool b);
void zero_alloc_switch(int x, int y);
int zero_alloc_rec_multi(int x, int i, size_t size1, size_t size2);
int zero_alloc_rec(int x, int i, size_t size1, size_t size2);
int zero_alloc_pseudo_rec1(int x, int y, int i, size_t size1, size_t size2);
int zero_alloc_pseudo_rec2(int x, int y, int i, size_t size1, size_t size2);
void zero_alloc_struct(int x, int y);
void zero_alloc_function_pointer(bool a, bool b, void (*f)(size_t* size, size_t size1, size_t size2, bool use_first));
void zero_alloc_cross_file(bool a, bool b);

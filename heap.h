#pragma once
#include <stddef.h>
#define BUFSIZE 1024

typedef struct {
    int heap_type;
    int (*cmp_f)(void *, void *);
    void **s_arr_p;
    int arr_size;
    int n_items;
} heap;

enum heap_type {Min_Heap, Max_Heap};

heap *init_heap(int (*cmp_f)(void *, void *), 
    enum heap_type type, 
    int initsize);
int is_empty(heap *h);
int push_heap(heap *h, void *s, size_t n);
void *pop_heap(heap *h);
void *peek(heap *h);
void free_heap(heap *h);
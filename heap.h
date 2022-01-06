#pragma once
#include <stddef.h>
#define BUFSIZE 1024

typedef struct {
    int (*cmp_f)(void *, void *);
    void **s_arr_p;
    int arr_size;
    int n_items;
} heap;

heap *init_heap(int (*cmp_f)(void *, void *));
int is_empty(heap *h);
int push_heap(heap *h, void *s, size_t n);
void *pop_heap(heap *h);
void *peek(heap *h);
void free_heap(heap *h);
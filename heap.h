/* API for array heap, accepts any type, supports min- and max-heap 
 * Memory is allocated dynamically, user bears the resposibility of freeing
 * popped elements
 */

#pragma once
#include <stddef.h>
#define BUFSIZE 1024

enum heap_type {Min_Heap, Max_Heap};

typedef struct {
    int heap_type; // Min-Heap or Max-heap
    int (*cmp_f)(void *, void *); // User defined function
    void **s_arr_p; // Array of pointers to elements
    int arr_size; // Array size
    int n_items; // Number of elements in the heap
} heap;

heap *init_heap(int (*cmp_f)(void *, void *), 
    enum heap_type type, 
    int initsize);
int is_empty(heap *h);
int push_heap(heap *h, void *s, size_t n);
void *pop_heap(heap *h);
void *peek(heap *h);
void free_heap(heap *h);
#pragma once
#include <stddef.h>
#define BUFSIZE 1024

typedef struct {
    char **s_arr_p;
    int arr_size;
    int n_items;
} heap;

heap *init_heap(void);
int is_empty(heap *h);
int push_heap(heap *h, char *s);
char *pop_heap(heap *h);
char *peek(heap *h);
void free_heap(heap *h);
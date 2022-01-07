# C Heap Library
A simple heap data-structure library for C. It can store any type provided that the used supplies the size of the elements. Elements may be added of removed using library calls.

To start:
1. `#include` heap.h
2. Define `cmp_f` that compares priorities between any two elements
3. Initialize a max-heap: `heap *h = init_heap(cmp_f, Max_Heap, 1024);` 

`h` now may hold 1024 values before the need to be resized automatically.

`cmp_f` is required to:
* Have the signature `int cmp_f(void *a, void *b)`
* Return a positive integer if `a` ranks higher than `b`
* Return a negative integer if `a` ranks lower than `b`
* Return zero if `a` and `b` rank equally

To add an element:

```c
// Push an int v
push_heap(h, &v, sizeof(int));

// Push a char c
push_heap(h, &c, sizeof(char));

// Push a string pointed to by s
push_heap(h, s, strlen(s) + 1); // Note that you need to add one to include the nul terminator
```

To get the element at the top (of the highest priority):

```c
int *top = pop_heap(h) // Removes the element from the heap restructuring the heap

int *peek_top = peek_heap(h); // Doesn't modify the heap
```

Note that it is the responsibity of the user to free `top`, as it has been seperated from the heap and won't be `free`'d upon the call to `free_heap` which only takes care of what's left in the heap.

# Reference sheet

| Action                                                      | Code                                          | Notes                                                            |
|-------------------------------------------------------------|-----------------------------------------------|------------------------------------------------------------------|
| Initialize min- or max-heap                                 | `heap *h = init_heap(cmp_f, Min_Heap, 1024);` | use `Min_Heap` or `Max_Heap` as `type` for respective heap type  |
| Check whether heap is empty                                 | `int empty = is_empty(h);`                    | returns `1` if empty, `0` otherwise                              |
| Push float `f` into heap                                    | `push_heap(h, &f, sizeof(f));`                |                                                                  |
| Get pointer to float on top of the heap without removing it | `float *top_fl = peek_heap(h);`               |                                                                  |
| Get pointer to float on top of the heap and removing it     | `float *popped_fl = pop_heap(h);`             | `free`ing `popped_fl` is up to you                               |
| Free heap and all elements it currently contains            | `heap_free(h)`                                |                                                                  |

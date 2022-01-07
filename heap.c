#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include "heap.h"

#define RESIZEMUL 2

int guarantee_space(heap *h);
int getLeftChildIndex(int parentIndex);
int getRightChildIndex(int parentIndex);
int getParentIndex(int childIndex);
int hasLeftChild(int parentIndex, int size);
int hasRightChild(int parentIndex, int size);
int hasParent(int childIndex);
void *leftChild(int parentIndex, heap *h);
void *rightChild(int parentIndex, heap *h);
void *parent(int childIndex, heap *h);
void swap(heap *h, int indexOne, int indexTwo);
void heapifyUp(heap *h);
void heapifyDown(heap *h);
int mycmp_f(int (*cmp_f)(void *, void *), void *a, void *b, enum heap_type type);

heap *init_heap(int (*cmp_f)(void *, void *), enum heap_type type, int initsize)
{
    heap *h = malloc(sizeof(heap));
    h->heap_type = type;
    h->cmp_f = cmp_f;
    h->s_arr_p = malloc(initsize * sizeof(void *));
    h->arr_size = initsize;
    h->n_items = 0;
    return h;
}

int is_empty(heap *h)
{
    return !h->n_items;
}

int push_heap(heap *h, void *s, size_t n)
{
    // Increase array size if full
    guarantee_space(h);

    // Copy string to heap
    void *new_s = malloc(n);
    if (new_s == NULL)
    {
        fprintf(stderr, "Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_s, s, n);
    // Append string pointer to array
    int index = h->n_items;
    (h->s_arr_p)[index] = new_s;

    // Account for new element
    (h->n_items)++;
    // Bubble up
    heapifyUp(h);
    // Success
    return 0;
}

void *pop_heap(heap *h)
{
    void *s = peek(h);
    void **s_arr = h->s_arr_p;
    int n_items = h->n_items;
    s_arr[0] = s_arr[n_items - 1];
    h->n_items--;
    heapifyDown(h);
    return s;
}

void *peek(heap *h)
{
    assert(!is_empty(h));
    return h->s_arr_p[0];
}

void free_heap(heap *h)
{
    void **s_arr = h->s_arr_p;
    int n = h->n_items;
    for (int i = 0; i < n; i++)
        free(s_arr[i]);
    free(s_arr);
    free(h);
}

int guarantee_space(heap *h)
{
    if (h->n_items == h->arr_size)
    {
        int newSize = h->arr_size * RESIZEMUL;
        h->s_arr_p = realloc(h->s_arr_p, newSize * sizeof(void *));
        {
            if (h->s_arr_p == NULL)
            {
                fprintf(stderr, "Could not grow array\n");
                exit(EXIT_FAILURE);
            }
        }
        h->arr_size = newSize;
    }
    // Success
    return 0;
}

int getLeftChildIndex(int parentIndex)
{
    return 2 * parentIndex + 1;
}

int getRightChildIndex(int parentIndex)
{
    return 2 * parentIndex + 2;
}

int getParentIndex(int childIndex)
{
    return (childIndex - 1) / 2;
}

int hasLeftChild(int parentIndex, int size)
{
    return getLeftChildIndex(parentIndex) < size;
}

int hasRightChild(int parentIndex, int size)
{
    return getRightChildIndex(parentIndex) < size;
}

int hasParent(int childIndex)
{
    return getParentIndex(childIndex) >= 0;
}

void *leftChild(int parentIndex, heap *h)
{
    return h->s_arr_p[getLeftChildIndex(parentIndex)];
}

void *rightChild(int parentIndex, heap *h)
{
    return h->s_arr_p[getRightChildIndex(parentIndex)];
}

void *parent(int childIndex, heap *h)
{
    return h->s_arr_p[getParentIndex(childIndex)];
}

void swap(heap *h, int indexOne, int indexTwo)
{
    void **arr = h->s_arr_p;
    void *temp = arr[indexOne];
    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = temp;
}

void heapifyUp(heap *h)
{
    void **s_arr = h->s_arr_p;
    int (*cmp_f)(void *, void *) = h->cmp_f;
    int index = h->n_items - 1;

    while (hasParent(index) &&
           mycmp_f(cmp_f, parent(index, h), s_arr[index], h->heap_type) > 0)
    {
        swap(h, getParentIndex(index), index);
        index = getParentIndex(index);
    }
}

void heapifyDown(heap *h)
{
    void **s_arr = h->s_arr_p;
    int (*cmp_f)(void *, void *) = h->cmp_f;
    int index = 0;
    int size = h->n_items;
    while (hasLeftChild(index, size))
    {
        int smallerChildIndex = getLeftChildIndex(index);
        if (hasRightChild(index, size))
        {
            if (mycmp_f(
                    cmp_f,
                    rightChild(index, h),
                    leftChild(index, h),
                    h->heap_type) < 0)
            {
                smallerChildIndex = getRightChildIndex(index);
            }
        }
        if (mycmp_f(
                cmp_f,
                s_arr[index],
                s_arr[smallerChildIndex],
                h->heap_type) < 0)
        {
            return;
        }
        else
        {
            swap(h, index, smallerChildIndex);
        }
        index = smallerChildIndex;
    }
}

int mycmp_f(int (*cmp_f)(void *, void *), void *a, void *b,
            enum heap_type type)
{
    if (type == Min_Heap)
        return cmp_f(a, b);
    else
        return cmp_f(a, b) * -1;
}
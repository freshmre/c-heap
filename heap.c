#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include "heap.h"

#define INITSZ 1024
#define RESIZEMUL 2

int guarantee_space(heap *h);
int getLeftChildIndex(int parentIndex);
int getRightChildIndex(int parentIndex);
int getParentIndex(int childIndex);
int hasLeftChild(int parentIndex, int size);
int hasRightChild(int parentIndex, int size);
int hasParent(int childIndex);
char *leftChild(int parentIndex, heap *h);
char *rightChild(int parentIndex, heap *h);
char *parent(int childIndex, heap *h);
void swap(heap *h, int indexOne, int indexTwo);
void heapifyUp(heap *h);
void heapifyDown(heap *h);

heap *init_heap(void) {
    heap *h = malloc(sizeof(heap));
    h->s_arr_p = malloc(INITSZ * sizeof(char *));
    h->arr_size = INITSZ;
    h->n_items = 0;
    return h;
}

int is_empty(heap *h) {
    return !h->n_items;
}

int push_heap(heap *h, char *s) {
    // Increase array size if full
    guarantee_space(h);

    // Copy string to heap
    char *new_s = malloc(strlen(s) + 1);
    strcpy(new_s, s);
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

char *pop_heap(heap *h) {
    char *s = peek(h);
    char **s_arr = h->s_arr_p;
    int n_items = h->n_items;
    s_arr[0] = s_arr[n_items - 1];
    h->n_items--;
    heapifyDown(h);
    return s;
}

char *peek(heap *h) {
    assert(!is_empty(h));
    return h->s_arr_p[0];
}

void free_heap(heap *h) {
    char **s_arr = h->s_arr_p;
    int n = h->n_items;
    for (int i = 0; i < n; i++)
        free(s_arr[i]);
    free(s_arr);
    free(h);
}

int guarantee_space(heap *h) {
    if (h->n_items == h->arr_size)
    {
        int newSize = h->arr_size * RESIZEMUL;
        h->s_arr_p = realloc(h->s_arr_p, newSize);
        h->arr_size *= RESIZEMUL;
    }
    // Success
    return 0;
}

int getLeftChildIndex(int parentIndex) {
    return 2 * parentIndex + 1;
}

int getRightChildIndex(int parentIndex) {
    return 2 * parentIndex + 2;
}

int getParentIndex(int childIndex) {
    return (childIndex - 1) / 2;
}

int hasLeftChild(int parentIndex, int size) {
    return getLeftChildIndex(parentIndex) < size;
}

int hasRightChild(int parentIndex, int size) {
    return getRightChildIndex(parentIndex) < size;
}

int hasParent(int childIndex) {
    return getParentIndex(childIndex) >= 0;
}

char *leftChild(int parentIndex, heap *h) {
    return h->s_arr_p[getLeftChildIndex(parentIndex)];
}

char *rightChild(int parentIndex, heap *h) {
    return h->s_arr_p[getRightChildIndex(parentIndex)];
}

char *parent(int childIndex, heap *h) {
    return h->s_arr_p[getParentIndex(childIndex)];
}

void swap(heap *h, int indexOne, int indexTwo) {
    char **arr = h->s_arr_p;
    char *temp = arr[indexOne];
    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = temp;
}

void heapifyUp(heap *h) {
    char **s_arr = h->s_arr_p;
    int index = h->n_items - 1;
    while (hasParent(index) && 
        strcasecmp(s_arr[getParentIndex(index)], s_arr[index]) > 0)
    {
        swap(h, getParentIndex(index), index);
        index = getParentIndex(index);
    }
}

void heapifyDown(heap *h) {
    char **s_arr = h->s_arr_p;
    int index = 0;
    int size = h->n_items;
    while (hasLeftChild(index, size))
    {
        int smallerChildIndex = getLeftChildIndex(index);
        if (hasRightChild(index, size) && 
        strcasecmp(rightChild(index, h), leftChild(index, h)) < 0)
        {
            smallerChildIndex = getRightChildIndex(index);
        }
        if (strcasecmp(s_arr[index], s_arr[smallerChildIndex]) < 0)
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
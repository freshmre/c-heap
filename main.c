#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "heap.h"
#include "tokenizer.h"

#define SIZE 1024

int mycmp(void *a, void *b);
int genRandInt(int a, int b);

int mycmp(void *a, void *b)
{
    return *(int *) a - *(int *) b;
}

/* Generate an int in [a, b] */
int genRandInt(int a, int b) {
    assert(a <= b);
    long v = rand();
    long range = b - a;
    return roundf(range * v / (float) RAND_MAX) + a;
}

/* Test max-heap, diff against sort -hr should output nothing */
int main(void)
{
    // Seed random
    srand(time(NULL));

    // Initialize max-heap
    heap *h = init_heap(mycmp, Max_Heap, SIZE);
    int i;
    int n;

    // Insert 100,000 random ints [-10000, 10000] into h
    for (i = 0; i < 100000; i++)
    {
        n = genRandInt(-10000, 10000);
        push_heap(h, &n, sizeof(n));
    }

    // Pop, display then free sorted ints
    int *v;
    for (i = 0; !is_empty(h); i++)
    {
        v = pop_heap(h);
        printf("%d\n", *v);
        free(v);
    }

    // Free heap
    free_heap(h);
}
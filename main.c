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

int genRandInt(int a, int b) {
    assert(a <= b);
    long v = rand();
    long range = b - a;
    return roundf(range * v / (float) RAND_MAX) + a;
}

int main(void)
{
    srand(time(NULL));

    heap *h = init_heap(mycmp);
    int i;
    int n;
    for (i = 0; i < 100000; i++)
    {
        n = genRandInt(-100, 100);
        push_heap(h, &n, sizeof(n));
    }

    int *v;
    for (i = 0; !is_empty(h); i++)
    {
        v = pop_heap(h);
        printf("%d\n", *v);
        free(v);
    }

    free_heap(h);
}
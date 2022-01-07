#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
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
    int r = rand();
    return r;
}

int main(void)
{
    srand(time(NULL));

    heap *h = init_heap(mycmp);
    int i;
    int n;
    for (i = 0; i < 10000; i++)
    {
        n = i;
        push_heap(h, &n, sizeof(n));
        printf("%d\n", h->n_items);
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
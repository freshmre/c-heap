#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "heap.h"
#include "tokenizer.h"

#define SIZE 1024

int mystrcmp(void *a, void *b);

int mystrcmp(void *a, void *b)
{
    return strcasecmp(a, b);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc == 2)
        fp = myfopen(argv[1], "r");
    else
        fp = stdin;

    char s[SIZE];
    heap *h = init_heap(mystrcmp);
    while (getword(fp, s, SIZE) != EOF)
        push_heap(h, s, strlen(s) + 1);

    char *sOut;
    for (int i = 0; !is_empty(h); i++)
    {
        sOut = pop_heap(h);
        printf("%s\n", sOut);
        free(sOut);
    }

    free_heap(h);
    fclose(fp);
}
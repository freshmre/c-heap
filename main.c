#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "heap.h"
#include "tokenizer.h"

#define SIZE 1024

void test_heap(void);
int mystrcmp(void *a, void *b);

int mystrcmp(void *a, void *b)
{
    // int lendiff = strlen(a) - strlen(b);
    // if (lendiff != 0)
    //     return lendiff;
    // else
        return strcasecmp(a, b);
}

void test_heap(void)
{
    char *buf[] = {"aa", "ab", "bc", "zz", "ak", "lm"};

    heap *h = init_heap(mystrcmp);
    for (size_t i = 0; i < sizeof(buf) / sizeof(*buf); i++)
        push_heap(h, buf[i], strlen(buf[i]) + 1);

    char *sOut;
    for (int i = 0; !is_empty(h); i++)
    {
        sOut = pop_heap(h);
        printf("%s\n", sOut);
        free(sOut);
    }
    free_heap(h);
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
    {
        push_heap(h, s, strlen(s) + 1);
    }

    char *sOut;
    for (int i = 0; !is_empty(h); i++)
    {
        sOut = pop_heap(h);
        printf("%s\n", sOut);
        free(sOut);
    }
    free_heap(h);
    fclose(fp);
    // test_heap();
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "heap.h"

#define SIZE 1024

void test_heap(void);
FILE *myfopen(const char *filename, const char *modes);
int getword(FILE *stream, char *buf, int bufsize);
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

FILE *myfopen(const char *filename, const char *modes)
{
    FILE *fp = fopen(filename, modes);
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file %s \n", filename);
        exit(EXIT_FAILURE);
    }
    return fp;
}

int getword(FILE *stream, char *buf, int bufsize)
{
    // Consume stream until word character or EOF is reached
    int c;
    do
    {
        c = getc(stream);
        if (c == EOF)
            return EOF;
    } while (!isalnum(c));

    // Consume stream and copy its word characters into buf
    // until non-word char, EOF or bufsize is reached
    int i = 0;
    do
    {
        buf[i++] = c;
        c = getc(stream);
        if (c == '-')
        {
            // Skip truncation hyphen
            if ((c = getc(stream)) == '\n')
                c = getc(stream);
            // Hyphen is part of the word
            else
                buf[i++] = '-';
        }
    } while ((isalnum(c) || c == '\'') && i < bufsize - 2);

    buf[i] = '\0';
    return 0;
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
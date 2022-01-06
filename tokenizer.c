#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tokenizer.h"

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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 1024

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
    } while ((isalnum(c) || c == '-') && i < bufsize - 2);

    buf[i] = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *filename;
    if (argc == 2)
        filename = argv[1];
    else
        filename = "test.txt";

    FILE *fp = myfopen(filename, "r");
    char s[SIZE];
    while (getword(fp, s, SIZE) != EOF)
        puts(s);
}
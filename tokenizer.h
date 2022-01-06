#pragma once
#include <stdio.h>

FILE *myfopen(const char *filename, const char *modes);
int getword(FILE *stream, char *buf, int bufsize);
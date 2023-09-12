#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include "getoutinfo.h"

char* CreateTextArray(size_t* line_amount, off_t* text_len)
{
    assert(line_amount);
    assert(text_len);

    FILE* fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("Input file: \"%s\"\n", FILE_NAME);
        return NULL;
    }

    *text_len = CountFileLength(FILE_NAME);

    char* buf = (char* ) calloc(*text_len + 1, sizeof(char));
        // for confidence, that program will have enough memory

    int ch = 0;
    int i = 0;

    if (fread(buf, sizeof(char), *text_len, fp) != *text_len)
        return NULL;

    if (buf[*text_len]    != '\0')
        buf[*text_len + 1] = '\0';

    for (int i = 0; i < *text_len; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            (*line_amount)++;
        }
    }

    fclose(fp);

    return buf;
}

char** CreatePtrArray(char* buf, const size_t line_amount, const off_t text_len)
{
    assert(buf);

    char** lines_pointers = (char** ) calloc(line_amount, sizeof(char*));

    if (lines_pointers ==  NULL)
        return NULL;

    lines_pointers[0] = (char* ) buf;

    size_t line = 1;

    for (off_t i = 0; i < text_len; i++)
    {
        if (buf[i] == '\0')
        {
            lines_pointers[line++] = buf + i + 1;
        }
    }

    return lines_pointers;
}


void PrintText(const char** lines_pointers, const size_t line_amount)
{
    assert(lines_pointers);

    for (size_t line = 0; line < line_amount; line++)
    {
        PrintLine(lines_pointers, line);
    }
}

void PrintLine(const char** lines_pointers, const size_t line)
{
    for (int i = 0; lines_pointers[line][i] != '\0'; i++)
    {
        putchar(lines_pointers[line][i]);
    }

    putchar('\n');
}

off_t CountFileLength(const char* file_name)
{
    assert(file_name);

    struct stat buf;
    stat(file_name, &buf);

    return buf.st_size;
}

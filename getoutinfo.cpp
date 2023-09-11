#include "stdio.h"
#include "assert.h"

#include "getoutinfo.h"

bool ReadFile(char* text, size_t* line_amount)
{
    assert(text);
    assert(line_amount);

    FILE* fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
        return false;

    int ch = fgetc(fp);
    int i = 0;

    while (ch != EOF)
    {
        text[i++] = ch;
        if (ch == '\n')
            (*line_amount)++;
        ch = fgetc(fp);
    }

    fclose(fp);

    return true;
}

void CreatePtrArray(char** lines_pointers, const char* text, const size_t text_len)
{
    assert(text);
    assert(lines_pointers);

    size_t line = 1;

    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == '\n')
            lines_pointers[line++] = (char* ) text + i + 1;
    }
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
    for (int i = 0; lines_pointers[line][i] != '\n'; i++)
    {
        putchar(lines_pointers[line][i]);
    }

    putchar('\n');
}

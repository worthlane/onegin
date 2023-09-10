#include "stdio.h"
#include "assert.h"

#include "getoutinfo.h"



bool ReadFile(char* text, int* line_amount)
{
    assert(text);
    assert(line_amount);

    FILE* fp = fopen(file_name, "r");

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

bool CreatePtrArray(char** lines_pointers, char* text)
{
    assert(text);
    assert(lines_pointers);

    int line = 1;

    for (int i = 0; i < text_len + 10; i++)
    {
        if (text[i] == '\n')
            lines_pointers[line++] = text + i + 1;
    }

    return true;
}


void PrintText(char** lines_pointers, int line_amount)
{
    assert(lines_pointers);

    for (int line = 0; line < line_amount - 1; line++)
    {
        PrintLine(lines_pointers, line);
    }
}

void PrintLine(char** lines_pointers, int line)
{
    for (int i = 0; lines_pointers[line][i] != '\n'; i++)
    {
        putchar(lines_pointers[line][i]);
    }

    putchar('\n');
}

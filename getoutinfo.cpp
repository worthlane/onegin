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

    // By the way, you can avoid some code repetition if you write this loop
    // in C-style:
    // int ch = 0;
    // while ((ch = fgetc()) != EOF)
    // {
    //     ...
    // }
    //
    // It is one of the very few cases where side effects aren't an issue.
    // In fact, this is a very commonly used style of creating read loops
    while (ch != EOF)
    {
        // Why don't you check the size of text? What if file is longer
        // than 1000 symbols?
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

    // What if text is shorter than 1010 characters?
    // Also, if I remember correctly, you allocate array only of size 1000.
    // If you use DED's compiler flags you will get a runtime error because of
    // address sanitizer.

    // + 10? WHY??????   --------v
    for (int i = 0; i < text_len + 10; i++)
    {
        if (text[i] == '\n')
            lines_pointers[line++] = text + i + 1;
    }

    // This seems to be the only way to exit function, so it only ever returns
    // one value. Why bother returning anything? This function can be void.
    return true;
}


void PrintText(char** lines_pointers, int line_amount)
{
    assert(lines_pointers);

    // Why do you need to subtract 1 here? |
    //                                     v
    for (int line = 0; line < line_amount - 1; line++)
    {
        PrintLine(lines_pointers, line);
    }
}

void PrintLine(char** lines_pointers, int line)
{
    // This would be much easier to do if lines were NUL-terminated
    // Also: There is no bounds check for `line`. What if index is too large?
    // What if it's negative?
    // Also also: What if there is no '\n' at the end of last line? Text files
    // in Linux are required to have terminating '\n', but you might encounter
    // invalid files.
    for (int i = 0; lines_pointers[line][i] != '\n'; i++)
    {
        putchar(lines_pointers[line][i]);
    }

    putchar('\n');
}

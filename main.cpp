#include "stdio.h"
#include "stdlib.h"

#include "getoutinfo.h"
#include "sorter.h"

int main()
{
    char* text = (char* ) calloc(text_len, sizeof(char));

    int line_amount = 1;

    if (!ReadFile(text, &line_amount))
        return 1;

    char** lines_pointers = (char** ) calloc(line_amount, sizeof(char*));
    lines_pointers[0] = text;

    CreatePtrArray(lines_pointers, text);

    StdSort(lines_pointers, line_amount);

    PrintText(lines_pointers, line_amount);

    free(lines_pointers);
    free(text);
}

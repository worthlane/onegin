#include "stdio.h"
#include "stdlib.h"

#include "getoutinfo.h"
#include "sorter.h"
#include "errors.h"

int main()
{

    size_t line_amount = 0;
    off_t text_len    = 0;

    char* buf = CreateTextArray(&line_amount, &text_len);

    if (buf == NULL)
        return (int) ERRORS::READ_FILE;

    char** lines_pointers = CreatePtrArray(buf, line_amount, text_len);

    if (lines_pointers == NULL)
        return (int) ERRORS::ALLOCATE_MEMORY;

    QSort(lines_pointers, 0, line_amount - 1); // increasing one for prevent crossing array borders

    PrintText((const char**) lines_pointers, line_amount);

    DestructPtrArray(lines_pointers);
    DestructTextArray(buf);
}


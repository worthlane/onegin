#include <stdio.h>
#include <stdlib.h>

#include "getoutinfo.h"
#include "sorter.h"
#include "errors.h"

int main()
{
    struct Storage info = {};

    int error = CreateTextStorage(&info);

    if (error != (int) ERRORS::NOT)
        return error;

    QSort(info.lines_ptrs, sizeof(char*), 0, info.line_amt - 1); // increasing one to prevent crossing array borders

    if(!PrintText((const char**) info.lines_ptrs, info.line_amt))
        return (int) ERRORS::PRINT_DATA;

    DestructLinePtrsArray(info.lines_ptrs);
    DestructTextBuf(info.buf);

    /*char* string1 = "afkdsnjdbsdbs";
    char* string2 = "8432dfkkfjdsjfoidgrkln\"";

    printf("%d", StdCompare(string1, string2));*/
}


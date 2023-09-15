#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "getoutinfo.h"
#include "sorter.h"
#include "errors.h"
#include "test.h"

// #define TEST

#ifdef TEST

int main()
{
    TestQSort();
    return 0;
}

#else

int main()
{
    struct Storage info = {};

    int error = CreateTextStorage(&info);

    if (error != (int) ERRORS::NOT)
        return error;

    ClearFile(OUTPUT_FILE);

    // -------- ALPHABET SORTING FROM BEGINNING --------

    qsort(info.lines_ptrs, info.line_amt - 1, sizeof(char*), &StdCompare);
    // increasing one to prevent crossing array borders

    if(!PrintText((const char**) info.lines_ptrs, info.line_amt,
                   "ALPHABET SORTING FROM BEGINNING"))
        return (int) ERRORS::PRINT_DATA;

    // -------------------------------------------------



    // ---------- ALPHABET SORTING FROM END ------------

    QSort(info.lines_ptrs, sizeof(char*), 0,
          info.line_amt - 1, &ReverseCompare);
    // increasing one to prevent crossing array borders

    if(!PrintText((const char**) info.lines_ptrs, info.line_amt,
                   "ALPHABET SORTING FROM END"))
        return (int) ERRORS::PRINT_DATA;

    // -------------------------------------------------



    // ------------ PRINT ORIGINAL VERSION -------------

    if(!PrintBuf(info.buf, info.text_len, "ORIGINAL VERSION"))
        return (int) ERRORS::PRINT_DATA;

    // -------------------------------------------------

    DestructTextStorage(&info);
}

#endif


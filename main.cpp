#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "getoutinfo.h"
#include "sorter.h"
#include "mylib/errors.h"
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

    if (error != (int) ERRORS::NONE)
        return error;

    ClearFile(OUTPUT_FILE);

    // -------- ALPHABET SORTING FROM BEGINNING --------

    qsort(info.lines, info.line_amt - 1, sizeof(struct LineParams), &StdCompare);
    // increasing one to prevent crossing array borders

    if(!PrintText(info.lines, info.line_amt,
                   "ALPHABET SORTING FROM BEGINNING"))
        return (int) ERRORS::PRINT_DATA;

    // -------------------------------------------------



    // ---------- ALPHABET SORTING FROM END ------------

    QSort(info.lines, sizeof(struct LineParams), 0,
          info.line_amt - 1, &ReverseCompare);
    // increasing one to prevent crossing array borders

    if(!PrintText(info.lines, info.line_amt,
                   "ALPHABET SORTING FROM END"))
        return (int) ERRORS::PRINT_DATA;

    // -------------------------------------------------



    // ------------ PRINT ORIGINAL VERSION -------------

    QSort(info.lines, sizeof(struct LineParams), 0,
          info.line_amt - 1, &AdressCompare);
    // increasing one to prevent crossing array borders

    if(!PrintText(info.lines, info.line_amt,
                   "ORIGINAL VERSION"))
        return (int) ERRORS::PRINT_DATA;

    // -------------------------------------------------

    DestructTextStorage(&info);
}

#endif


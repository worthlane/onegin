#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "input_and_output.h"
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

int main(const int argc, const char* argv[])
{
    struct Storage info = {};
    struct ErrorInfo error = {ERRORS::NONE};

    CreateTextStorage(&info, &error);

    if (error.code !=  ERRORS::NONE)
        return PrintError(&error);

    EraseFile(OUTPUT_FILE);

    FILE* outstream = fopen(OUTPUT_FILE, "w");

    if (!outstream)
    {
        error.code  = ERRORS::OPEN_FILE;
        error.param = (char*) OUTPUT_FILE;
        return PrintError(&error);
    }

    // -------- ALPHABET SORTING FROM BEGINNING --------

    qsort(info.lines, info.line_amt - 1, sizeof(struct LineParams), &StdCompare);
    // increasing one to prevent crossing array borders

    PrintHeader(outstream, "ALPHABET SORTING FROM BEGINNING");

    if(!PrintAllLines(outstream, info.lines, info.line_amt, &error))
    {
        error.param = (char*) OUTPUT_FILE;
        return PrintError(&error);
    }

    // -------------------------------------------------

    PrintSeparator(outstream);

    // ---------- ALPHABET SORTING FROM END ------------
    
    QSort(info.lines, sizeof(struct LineParams), 0,
          info.line_amt - 1, &ReverseCompare);
    // increasing one to prevent crossing array borders

    PrintHeader(outstream, "ALPHABET SORTING FROM END");

    if(!PrintAllLines(outstream, info.lines, info.line_amt, &error))
    {
        error.param = (char*) OUTPUT_FILE;
        return PrintError(&error);
    }

    // -------------------------------------------------

    PrintSeparator(outstream);

    // ------------ PRINT ORIGINAL VERSION -------------

    QSort(info.lines, sizeof(struct LineParams), 0,
          info.line_amt - 1, &AdressCompare);
    // increasing one to prevent crossing array borders

    PrintHeader(outstream, "ORIGINAL VERSION");

    if(!PrintAllLines(outstream, info.lines, info.line_amt, &error))
    {
        error.param = (char*) OUTPUT_FILE;
        return PrintError(&error);
    }

    // -------------------------------------------------

    fclose(outstream);

    DestructTextStorage(&info);
}

#endif

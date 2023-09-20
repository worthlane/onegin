#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "input_and_output.h"
#include "sorter.h"
#include "mylib/errors.h"
#include "test.h"

// #define TEST

static const char* INPUT_FILE  = "assets/onegin.txt";
static const char* OUTPUT_FILE = "assets/output.txt";

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

    const char* INPUT_FILE_NAME = "";
    const char* OUTPUT_FILE_NAME = "";

    if (argc == 1)
    {
        INPUT_FILE_NAME  = INPUT_FILE;
        OUTPUT_FILE_NAME = OUTPUT_FILE;
    }
    else if (argc == 2)
    {
        INPUT_FILE_NAME  = argv[1];
        OUTPUT_FILE_NAME = OUTPUT_FILE;
    }
    else
    {
        INPUT_FILE_NAME  = argv[1];
        OUTPUT_FILE_NAME = argv[2];
    }

    CreateTextStorage(&info, &error, INPUT_FILE_NAME);

    if (error.code !=  ERRORS::NONE)
        return PrintError(&error);

    if (!EraseFile(OUTPUT_FILE_NAME))
        {
            error.code = ERRORS::OPEN_FILE;
            error.data = (char*) OUTPUT_FILE_NAME;
            return PrintError(&error);
        }

    FILE* outstream = fopen(OUTPUT_FILE_NAME, "w");

    if (!outstream)
    {
        error.code = ERRORS::OPEN_FILE;
        error.data = (char*) OUTPUT_FILE_NAME;
        return PrintError(&error);
    }

    // -------- ALPHABET SORTING FROM BEGINNING --------

    qsort(info.lines, info.line_amt - 1, sizeof(struct LineInfo), &StdCompare);
    // decreasing one to prevent crossing array borders

    PrintHeader(outstream, "ALPHABET SORTING FROM BEGINNING");

    if(!PrintAllLines(outstream, info.lines, info.line_amt, &error))
    {
        error.data = (char*) OUTPUT_FILE_NAME;
        return PrintError(&error);
    }

    // -------------------------------------------------

    PrintSeparator(outstream);

    // ---------- ALPHABET SORTING FROM END ------------

    QSort(info.lines, sizeof(struct LineInfo), 0,
          info.line_amt - 1, &ReverseCompare);
    // decreasing one to prevent crossing array borders

    PrintHeader(outstream, "ALPHABET SORTING FROM END");

    if(!PrintAllLines(outstream, info.lines, info.line_amt, &error))
    {
        error.data = (char*) OUTPUT_FILE_NAME;
        return PrintError(&error);
    }

    // -------------------------------------------------

    PrintSeparator(outstream);

    // ------------ PRINT ORIGINAL VERSION -------------

    QSort(info.lines, sizeof(struct LineInfo), 0,
          info.line_amt - 1, &AdressCompare);
    // decreasing one to prevent crossing array borders

    PrintHeader(outstream, "ORIGINAL VERSION");

    if(!PrintAllLines(outstream, info.lines, info.line_amt, &error))
    {
        error.data = (char*) OUTPUT_FILE_NAME;
        return PrintError(&error);
    }

    // -------------------------------------------------

    fclose(outstream);

    DestructTextStorage(&info);
}

#endif

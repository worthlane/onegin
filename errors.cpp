#include <stdio.h>

#include "mylib/errors.h"
#include "mylib/colorlib.h"

int PrintError(struct ErrorInfo* error)
{
    switch (error->code)
    {
        case (ERRORS::NONE):
            return (int) error->code;

        case (ERRORS::OPEN_FILE):
            PRINT_RED_TEXT(stderr, "OPEN FILE ERROR\n"
                                 "FAILED TO OPEN FILE \"%s\"\n", error->data);
            return (int) error->code;

        case (ERRORS::READ_FILE):
            PRINT_RED_TEXT(stderr, "READ FILE ERROR\n"
                                 "FAILED TO READ INFO FROM FILE \"%s\"\n", error->data);
            return (int) error->code;

        case (ERRORS::ALLOCATE_MEMORY):
            PRINT_RED_TEXT(stderr, "MEMORY ALLOCATE ERROR\n"
                                 "FAILED TO ALLOCATE MEMORY IN \"%s\"\n", error->data);
            return (int) error->code;

        case (ERRORS::PRINT_DATA):
            PRINT_RED_TEXT(stderr, "DATA PRINT ERROR\n"
                                 "FAILED TO PRINT DATA IN \"%s\"\n", error->data);
            return (int) error->code;

        default:
            PRINT_RED_TEXT(stderr, "UNKNOWN ERROR\n", "");
            return (int) ERRORS::UNKNOWN;
    }
}

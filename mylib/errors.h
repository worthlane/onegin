#ifndef __ERRORS_H
#define __ERRORS_H

/*! \file
* \brief Contains enumerated errors
*/

enum class ERRORS
{
    NONE            = 0, /// not an error
    OPEN_FILE       = 1, /// error while opening file
    READ_FILE       = 2, /// error while reading file
    ALLOCATE_MEMORY = 3, /// error with memory allocating
    PRINT_DATA      = 4  /// error while printing data
};

#endif

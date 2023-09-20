#ifndef __ERRORS_H
#define __ERRORS_H

/*! \file
* \brief Contains enumerated errors
*/

enum class ERRORS
{
    NONE = 0,               /// not an error

    OPEN_FILE,              /// error while opening file
    READ_FILE,              /// error while reading file

    ALLOCATE_MEMORY,        /// error with memory allocating

    PRINT_DATA,             /// error while printing data

    UNKNOWN                 /// unknown error
};

struct ErrorInfo
{
    ERRORS code;
    char* data;
};

/************************************************************//**
 * @brief Prints error in stderr
 *
 * @param[in] error error structure
 * @return int error code
 ************************************************************/
int PrintError(struct ErrorInfo* error);

#endif

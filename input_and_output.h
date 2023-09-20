#ifndef __GETOUTINFO_H
#define __GETOUTINFO_H

#include <stdio.h>
#include <stdlib.h>

/*! \file
* \brief Contains info about functions, that get data and print it
*/

static const char* INPUT_FILE  = "assets/onegin.txt";  /// open file name
static const char* OUTPUT_FILE = "assets/output.txt";  /// open file name


/************************************************************//**
 * @brief Contains info about one line
 ************************************************************/
struct LineParams
{
    char* string; /// line
    size_t len;   /// length of string
};

/************************************************************//**
 * @brief Storage with info about buffer
 ************************************************************/
struct Storage
{
    size_t line_amt;            /// amount of lines
    off_t text_len;             /// amount of symbols in buffer
    char* buf;                  /// buffer
    struct LineParams* lines;   /// structure with info about line
};

/************************************************************//**
 * @brief counts amount of symbols in input file
 *
 * @param[in] file_name name of opening file
 * @return amount of symbols in file
 *************************************************************/
off_t GetFileLength(const char* file_name);

/************************************************************//**
 * @brief Prints all lines from buffer
 *
 * @param[in] stream stream, where lines are printing
 * @param[in] lines array of lines structures
 * @param[in] line_amount amount of lines
 * @param[out] error error structure
 * @return true if there was no error
 * @return false if there was an error
 *************************************************************/
bool PrintAllLines(FILE* stream, const struct LineParams* lines,
                   const size_t line_amount, struct ErrorInfo* error);

/************************************************************//**
 * @brief Prints one line
 *
 * @param[in] stream stream, where line is printing
 * @param[in] line structure with info about line, that function prints
 * @param[out] error error structure
 ************************************************************/
void PrintOneLine(FILE* stream, const struct LineParams* line, struct ErrorInfo* error);

/************************************************************//**
 * @brief Create a Text Storage object
 *
 * @param[in] info storage
 * @param[out] error error structure
 * @return int error code
 ************************************************************/
int CreateTextStorage(struct Storage* info, struct ErrorInfo* error);

/************************************************************//**
 * @brief Clears file from text in it
 *
 * @param[in] FILE_NAME file name
 * @return true if file cleared succesfully
 * @return false if there was an error while clearing file
 ************************************************************/
bool EraseFile(const char* FILE_NAME);

/************************************************************//**
 * @brief Prints buffer
 *
 * @param[in] stream stream, where buffer is printing
 * @param[in] buf buffer
 * @param[in] buf_len length of buffer
 ************************************************************/
void PrintBuf(FILE* stream, const char* buf, const size_t buf_len);

/************************************************************//**
 * @brief Prints header
 *
 * @param[in] stream stream, where header is printing
 * @param[in] header header
 * @return true if header printed succesfully
 * @return false if there was an error
 ************************************************************/
bool PrintHeader(FILE* stream, const char* header);

/************************************************************//**
 * @brief Prints separator
 *
 * @param[in] stream stream, where separator is printing
 * @return true if separator printed succesfully
 * @return false if there was an error
 ************************************************************/
bool PrintSeparator(FILE* stream);

/************************************************************//**
 * @brief Destructs a Text Storage object
 *
 * @param[in] info storage
 ************************************************************/
inline void DestructTextStorage(struct Storage* info)
{
    free(info->lines);
    free(info->buf);
}

/************************************************************//**
 * @brief Prints error in stderr
 *
 * @param[in] error error structure
 * @return int error code
 ************************************************************/
int PrintError(struct ErrorInfo* error);

#endif

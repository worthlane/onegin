#ifndef __GETOUTINFO_H
#define __GETOUTINFO_H

#include <stdio.h>
#include <stdlib.h>

/*! \file
* \brief Contains info about functions, that get data and print it
*/

static const char* INPUT_FILE  = "assets/onegin.txt";  /// open file name
static const char* OUTPUT_FILE = "assets/output.txt";  /// open file name

struct LineParams
{
    char* string;
    size_t len;
};

/************************************************************//**
 * @brief Storage with info about buffer
 ************************************************************/
struct Storage
{
    size_t line_amt;            /// amount of lines
    off_t text_len;             /// amount of symbols in buffer
    char* buf;                  /// buffer
    struct LineParams* lines;
};

/************************************************************//**
 * @brief counts amount of symbols in input file
 *
 * @param[in] file_name name of opening file
 * @return amount of symbols in file
 *************************************************************/
off_t GetFileLength(const char* file_name);

int FindLinesStart(struct Storage* info, struct ErrorInfo* error);

bool PrintAllLines(FILE* stream, const struct LineParams* lines,
                   const size_t line_amount, struct ErrorInfo* error);

void PrintOneLine(FILE* stream, const struct LineParams* line, struct ErrorInfo* error);

/************************************************************//**
 * @brief Create a Text Storage object
 *
 * @param[in] info storage
 * @return int error
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

void PrintBuf(FILE* stream, const char* buf, const size_t text_len);

bool PrintHeader(FILE* stream, const char* header);

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

int PrintError(struct ErrorInfo* error);

#endif

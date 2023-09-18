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
off_t CountFileLength(const char* file_name);

/************************************************************//**
 * @brief Reads text from file, allocates memory for text buffer,
 *
 * @param[in] info structure with info about text buffer
 * @return char* pointer on text buffer
 * @return NULL if there was an error
 ************************************************************/
char* CreateTextBuf(struct Storage* info);

struct LineParams* CreateLinePtrsArray(struct Storage* info);

bool PrintText(const struct LineParams* lines, const size_t line_amount, const char* header);

void PrintLine(const struct LineParams* lines, const size_t line, FILE* fp);

/************************************************************//**
 * @brief Destructs text buffer and clears memory
 *
 * @param[in] buf text buffer
 ************************************************************/
inline void DestructTextBuf(char* buf)
{
    free(buf);
}

inline void DestructLinePtrsArray(struct LineParams* lines)
{
    free(lines);
}

/************************************************************//**
 * @brief Create a Text Storage object
 *
 * @param[in] info storage
 * @return int error
 ************************************************************/
int CreateTextStorage(struct Storage* info);

/************************************************************//**
 * @brief Clears file from text in it
 *
 * @param[in] FILE_NAME file name
 * @return true if file cleared succesfully
 * @return false if there was an error while clearing file
 ************************************************************/
bool ClearFile(const char* FILE_NAME);

/************************************************************//**
 * @brief Prints info from buffer
 *
 * @param[in] buf buffer
 * @param[in] text_len amount of symbols in file
 * @param[in] header header
 * @return true if info printed succesfully
 * @return false if there was an error
 ************************************************************/
bool PrintBuf(const char* buf, const size_t text_len, const char* header);

/************************************************************//**
 * @brief Destructs a Text Storage object
 *
 * @param[in] info storage
 ************************************************************/
inline void DestructTextStorage(struct Storage* info)
{
    DestructLinePtrsArray(info->lines);
    DestructTextBuf(info->buf);
}

#endif

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
 * @brief Storage with info about buffer
 ************************************************************/
struct Storage
{
    size_t line_amt;   /// amount of lines
    off_t text_len;    /// amount of symbols in buffer
    char* buf;         /// buffer
    char** lines_ptrs; /// array with each line pointers
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

/************************************************************//**
 * @brief Allocates memory for array, that contains pointers on each new line start (in text buffer)
 *
 * @param[in] info structure with info about text buffer
 * @return char** pointer on array of line pointers
 * @return NULL if there was an error
 ************************************************************/
char** CreateLinePtrsArray(struct Storage* info);

/************************************************************//**
 * @brief Prints text in right lines order
 *
 * @param[in] lines_pointers array of line pointers
 * @param[in] line_amount amount of lines
 * @param[in] header header
 * @return true if text printed succesfully
 * @return false if there was an error
 ************************************************************/
bool PrintText(const char** lines_pointers, const size_t line_amount, const char* header);

/************************************************************//**
 * @brief Prints one line from buffer
 *
 * @param[in] lines_pointers array of each line pointers
 * @param[in] line number of line
 ************************************************************/
void PrintLine(const char** lines_pointers, const size_t line, FILE* fp);

/************************************************************//**
 * @brief Destructs text buffer and clears memory
 *
 * @param[in] buf text buffer
 ************************************************************/
inline void DestructTextBuf(char* buf)
{
    free(buf);
}

/************************************************************//**
 * @brief Destructs array of line pointers and clears memory
 *
 * @param[in] lines_pointers array of each line pointers
 ************************************************************/
inline void DestructLinePtrsArray(char** lines_pointers)
{
    free(lines_pointers);
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
    DestructLinePtrsArray(info->lines_ptrs);
    DestructTextBuf(info->buf);
}

#endif

#ifndef __GETOUTINFO_H
#define __GETOUTINFO_H

#include <stdio.h>
#include <stdlib.h>

/*! \file
* \brief Contains info about functions, that get data and print it
*/

static const char* INPUT_FILE  = "onegin.txt";  /// open file name
static const char* OUTPUT_FILE = "output.txt"; /// open file name

struct Storage
{
    size_t line_amt;
    off_t text_len;
    char* buf;
    char** lines_ptrs;
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
 * @brief Prints text from buffer
 *
 * @param[in] lines_pointers array of each line pointers
 * @param[in] line_amount amount of lines in buffer
 * @return true if data succesfully printed
 * @return false if there was an error
 ************************************************************/
bool PrintText(const char** lines_pointers, const size_t line_amount);

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

int CreateTextStorage(struct Storage* info);

#endif

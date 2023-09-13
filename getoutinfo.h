#ifndef __GETOUTINFO_H
#define __GETOUTINFO_H

#include <stdio.h>
#include <stdlib.h>

/*! \file
* \brief Contains info about functions, that get data and print it
*/

static const char* FILE_NAME = "input.txt"; /// open file name

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
 * @param[in] line_amount amount of lines in file
 * @param[in] text_len amount of symbols in file
 * @return char* pointer on text buffer
 * @return NULL if there was an error
 ************************************************************/
char* CreateTextBuf(size_t* line_amount, off_t* text_len);

/************************************************************//**
 * @brief Allocates memory for array, that contains pointers on each new line start (in text buffer)
 *
 * @param[in] buf text buffer
 * @param[in] line_amount amount of lines in buffer
 * @param[in] text_len amount of symbols in buffer
 * @return char** pointer on array of line pointers
 * @return NULL if there was an error
 ************************************************************/
char** CreateLinePtrsArray(char* buf, const size_t line_amount, const off_t text_len);

/************************************************************//**
 * @brief Prints text from buffer
 *
 * @param[in] lines_pointers array of each line pointers
 * @param[in] line_amount amount of lines in buffer
 ************************************************************/
void PrintText(const char** lines_pointers, const size_t line_amount);

/************************************************************//**
 * @brief Prints one line from buffer
 *
 * @param[in] lines_pointers array of each line pointers
 * @param[in] line number of line
 ************************************************************/
void PrintLine(const char** lines_pointers, const size_t line);

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

#endif

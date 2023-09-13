#ifndef __SORTER_H
#define __SORTER_H

#include <stdio.h>

/*! \file
* \brief contains comparing functions
*/

/************************************************************//**
 * @brief Compares strings from their beginning (standart alphabet compare)
 *
 * @param[in] first_line first string
 * @param[in] second_line second string
 * @return -1 if first line must be first
 * @return 0 if strings are same, or one of them is prefix of another
 * @return 1 if second string must be first
 *************************************************************/
int StdCompare(char* first_line, char* second_line);

/************************************************************//**
 * @brief Runs insertion sorting
 *
 * @param[in] lines_pointers array of each line pointers
 * @param[in] line_amount amount of lines in buffer
 ************************************************************/
void InsertionSort(char** lines_pointers, size_t line_amount);

/************************************************************//**
 * @brief Runs quick sorting
 *
 * @param[in] data strings array
 * @param[in] left left border
 * @param[in] right right border
 ************************************************************/
void QSort(char** data, size_t left, size_t right);

/************************************************************//**
 * @brief Does partition for quick sort
 *
 * @param[in] data strings array
 * @param[in] left left border
 * @param[in] right right border
 * @return size_t middle element number
 *************************************************************/
size_t Partition(char** data, size_t left, size_t right);

/************************************************************//**
 * @brief Enums result of comparing strings
 ************************************************************/
enum Comparison
{
    LESS  = -1,
    EQUAL =  0,
    MORE  =  1
};

#endif

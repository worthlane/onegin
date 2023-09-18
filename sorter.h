#ifndef __SORTER_H
#define __SORTER_H

#include <stdio.h>

/*! \file
* \brief contains comparing functions
*/

typedef int comparator_t(const void* first, const void* second);

/************************************************************//**
 * @brief Swaps two elements in memory
 *
 * @param[in] ptr1 first element
 * @param[in] ptr2 second element
 * @param[in] size element size
 ************************************************************/

void Swap(void* ptr1, void* ptr2, size_t size);

/************************************************************//**
 * @brief Compares two strings from beginning
 *
 * @param[in] first_line first line
 * @param[in] second_line second line
 * @return -1 if first line must go first
 * @return 0 if one of strings is prefix of another
 * @return 1 if second string must go first
 ***********************************************************/

int StdCompare(const void* first_line, const void* second_line);

/************************************************************//**
 * @brief Compares two strings from end
 *
 * @param[in] first_line first line
 * @param[in] second_line second line
 * @return -1 if first line must go first
 * @return 0 if one of strings is prefix of another
 * @return 1 if second string must go first
 ***********************************************************/

int ReverseCompare(const void* first_line, const void* second_line);

/************************************************************//**
 * @brief Quick sorting
 *
 * @param[in] data sorting data
 * @param[in] size size of each element in data
 * @param[in] left left border
 * @param[in] right right border
 * @param[in] Compare comparator function
 ***********************************************************/

void QSort(const void* data, const size_t size, const size_t left, const size_t right,
           comparator_t* Compare);

/************************************************************//**
 * @brief Partition in quick sorting
 *
 * @param[in] data sorting data
 * @param[in] size size of each element in data
 * @param[in] left left border
 * @param[in] right right border
 * @param[in] Compare comparator function
 ***********************************************************/

size_t Partition(const void* data, const size_t size, const size_t left, const size_t right,
                 comparator_t* Compare);


/************************************************************//**
 * @brief Enums result of comparing strings
 ************************************************************/
enum Comparison
{
    LESS     = -1,
    EQUAL    =  0,
    GREATER  =  1
};

/************************************************************//**
 * @brief Compares two adresses, that are containing in memory
 *
 * @param[in] first_adress first adress
 * @param[in] second_adress second adress
 * @return -1 if first_adress < second_adress
 * @return 0 if first_adress = second_adress
 * @return 1 if first_adress > second_adress
 ***********************************************************/
int AdressCompare(const void* first_adress, const void* second_adress);

#endif

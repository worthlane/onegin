#ifndef __SORTER_H
#define __SORTER_H

#include <stdio.h>

/*! \file
* \brief contains comparing functions
*/


int StdCompare(const void* first_line, const void* second_line);

int ReverseCompare(const void* first_line, const void* second_line);

void QSort(void* data, const size_t size, const size_t left, const size_t right,
           int (*Compare) (const void *, const void *));

size_t Partition(void* data, const size_t size, const size_t left, const size_t right,
                 int (*Compare) (const void *, const void *));

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

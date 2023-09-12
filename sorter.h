#ifndef __SORTER_H
#define __SORTER_H

#include <stdio.h>

int StdCompare(char* first_line, char* second_line);

void StdSort(char** lines_pointers, size_t line_amount);

void QSort(char** data, size_t left, size_t right);

size_t Partition(char** data, size_t left, size_t right);

enum Comparison
{
    LESS  = -1,
    EQUAL =  0,
    MORE  =  1
};

#endif

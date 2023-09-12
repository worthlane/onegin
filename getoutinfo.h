#ifndef __GETOUTINFO_H
#define __GETOUTINFO_H

#include <stdio.h>
#include <stdlib.h>

static const char* FILE_NAME = "input.txt";

off_t CountFileLength(const char* file_name);

char* CreateTextArray(size_t* line_amount, off_t* text_len);

char** CreatePtrArray(char* buf, const size_t line_amount, const off_t text_len);

void PrintText(const char** lines_pointers, const size_t line_amount);
void PrintLine(const char** lines_pointers, const size_t line);

inline void DestructTextArray(char* buf)
{
    free(buf);
}

inline void DestructPtrArray(char** lines_pointers)
{
    free(lines_pointers);
}



#endif

#ifndef __GETOUTINFO_H
#define __GETOUTINFO_H

static const char* FILE_NAME = "input.txt";

bool ReadFile(char* text, size_t* line_amount);

void CreatePtrArray(char** lines_pointers, const char* text, const size_t text_len);

void PrintText(const char** lines_pointers, const size_t line_amount);
void PrintLine(const char** lines_pointers, const size_t line);

#endif

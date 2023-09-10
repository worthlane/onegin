#include "stdio.h"

static const char* file_name = "input.txt";
static const int text_len = 1000;

bool ReadFile(char* text, int* line_amount);

bool CreatePtrArray(char** lines_pointers, char* text);

void PrintText(char** lines_pointers, int line_amount);

void PrintLine(char** lines_pointers, int line);

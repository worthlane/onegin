// Typically, header files are guarded against multiple includes of the
//  same file.
//
// Example:
// #ifndef __GETOUTINFO_H
// #define __GETOUTINFO_H
//
// <Your code here>
//
// #endif
//

// System headers are typically included like this:
// #include <stdio.h>
#include "stdio.h"


static const char* file_name = "input.txt";
static const int text_len = 1000;

// What do this four functions have in common? Why are they in the same file?
// Also, what does "getoutinfo" mean? Does it describe the common purpose of
// these functions?

// What file does it read? Maybe you can pass file name as parameter?
// Also: Can `line_amount` be negative? Why does it have type `int`?
// Sizes and indices are usually represented with type `size_t`
bool ReadFile(char* text, int* line_amount);

// CreatePtrArray? What kind of pointers does it create?
// Also: why is `text` not `const char*`? Does this function modify text?
bool CreatePtrArray(char** lines_pointers, char* text);

// Can `line_amount` be negative? Why does it have type `int`?
// Also: what text does it print? There is no parameter named `text`.
void PrintText(char** lines_pointers, int line_amount);

// Can `line` be negative? Why does it have type `int`?
void PrintLine(char** lines_pointers, int line);

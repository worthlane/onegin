#include "stdio.h"
#include "ctype.h"

#include "sorter.h"
#include "getoutinfo.h"

// This function is only used within this file. Why is it declared in header for
// everyone to see?
void Swap(char** ptr1, char** ptr2)
{
    // WHAT IS THIS INDENT LEVEL????????????????????
    // I understand that you are trying to align ptr1 and ptr2,
    // but this looks horrible!!!!
    char* temp = *ptr1;
                 *ptr1 = *ptr2;
                         *ptr2 = temp;
}

// This function is only used within this file. Why is it declared in header for
// everyone to see?
// Also: Why does it return `bool`? Does it return true if first < second?
// If first > second? If first == second?
// Either use more descriptive name or make it return int as follows:
//    < 0 if first < second
//    = 0 if first == second
//    > 0 if first > second
bool StdCompare(char* first_line, char* second_line)
{
    // There is a function strcasecmp/strncasecmp in <strings.h> for this
    // Again, it will be easier to work with strings if they are NUL-terminated
    for (int i = 0; first_line[i]  != '\n' &&
                    second_line[i] != '\n'; i++)
        {
            int second = toupper(second_line[i]);
            int first  = toupper(first_line[i]);
            if (second == first)
                continue;
            else if (second < first)
                return false;
            else
                return true;
        }
    return true;
}

void StdSort(char** lines_pointers, int line_amount)
{
    for (int line1 = 0; line1 < line_amount - 1; line1++)
    {
        for (int line2 = line1 + 1; line2 < line_amount - 1; line2++)
        {
            if(!StdCompare(lines_pointers[line1],    lines_pointers[line2]))
                    Swap(&(lines_pointers[line1]), &(lines_pointers[line2]));
        }
    }
}


#include "stdio.h"
#include "ctype.h"

#include "sorter.h"
#include "getoutinfo.h"

void Swap(char** ptr1, char** ptr2)
{
    char* temp = *ptr1;
                 *ptr1 = *ptr2;
                         *ptr2 = temp;
}

bool StdCompare(char* first_line, char* second_line)
{
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


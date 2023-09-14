#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <assert.h>

#include "sorter.h"
#include "getoutinfo.h"

#define DEBUG

static inline void Swap(char** ptr1, char** ptr2)
{
    char* temp = *ptr1;
    *ptr1      = *ptr2;
    *ptr2      = temp;
}

//-------------------------------------------------------------------------------------------

int StdCompare(char* first_line, char* second_line)
{
    int first_ptr  = 0;
    int second_ptr = 0;

    while (first_line[first_ptr] != '\0' && second_line[second_ptr] != '\0')
        {
            if (isalpha(first_line[first_ptr]) && isalpha(second_line[second_ptr]))
            {
                int second = toupper(second_line[second_ptr++]);
                int first  = toupper(first_line[first_ptr++]);
                if (second == first)
                    continue;
                else if (first < second)
                    return LESS;
                else
                    return MORE;
            }
            else if (!isalpha(first_line[first_ptr]))
            {
                first_ptr++;
            }
            else if (!isalpha(second_line[second_ptr]))
            {
                second_ptr++;
            }
        }

    return EQUAL;
}

//-------------------------------------------------------------------------------------------

void InsertionSort(char** lines_pointers, size_t line_amount)
{
    for (size_t line1 = 0; line1 < line_amount; line1++)
    {
        for (size_t line2 = line1 + 1; line2 < line_amount; line2++)
        {
            if(StdCompare(lines_pointers[line1],    lines_pointers[line2]) == MORE)
                   Swap(&(lines_pointers[line1]), &(lines_pointers[line2]));
        }
    }
}

//-------------------------------------------------------------------------------------------

void QSort(char** data, size_t left, size_t right) // TODO const
{
    assert(data);
    assert(left <= right);

	if (left < right)
	{
        if (right - left == 1)
		{
			if (StdCompare(data[left], data[right]) != LESS)
			{
				Swap(&data[right], &data[left]);
			}
		}
        else
        {
		    size_t mid = Partition(data, left, right);

		    QSort(data, left, mid);
		    QSort(data, mid + 1, right);
        }
	}
}

//-------------------------------------------------------------------------------------------

size_t Partition(char** data, size_t left, size_t right)
{
    assert(data);
    assert(left <= right);

    char* mid = data[(left + right) / 2];

    size_t left_ptr  = left;
    size_t right_ptr = right;

    while (left_ptr <= right_ptr)
    {
        while (StdCompare(data[left_ptr], mid) == LESS && right_ptr > left_ptr)
        {
            left_ptr++;
        }

        while (StdCompare(data[right_ptr], mid) == MORE && right_ptr > left_ptr)
        {
            right_ptr--;
        }

		if (left_ptr >= right_ptr)
			break;

        Swap(&data[left_ptr], &data[right_ptr]);

		left_ptr++;
		right_ptr--;

    }
    return right_ptr;
}



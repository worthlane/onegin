#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <assert.h>

#include "sorter.h"
#include "getoutinfo.h"

#define DEBUG

static void Swap(void* ptr1, void* ptr2);

static void Swap(void* ptr1, void* ptr2)
{
    char** pointer1 = (char**) ptr1;
    char** pointer2 = (char**) ptr2;

    char* temp = *pointer1;
    *pointer1  = *pointer2;
    *pointer2  = temp;
}

//-------------------------------------------------------------------------------------------

int StdCompare(const void* first_line, const void* second_line)
{
    assert(first_line);
    assert(second_line);

    const char* first_string  = *((const char**) first_line);
    const char* second_string = *((const char**) second_line);

    int first_ptr  = 0;
    int second_ptr = 0;

    while (first_string[first_ptr] != '\0' && second_string[second_ptr] != '\0')
    {
        if (isalpha(first_string[first_ptr]) && isalpha(second_string[second_ptr]))
        {
            int second = toupper(second_string[second_ptr++]);
            int first  = toupper(first_string[first_ptr++]);
            if (second == first)
                continue;
            else if (first < second)
                return LESS;
            else
                return MORE;
        }
        else if (!isalpha(first_string[first_ptr]))
        {
            first_ptr++;
        }
        else if (!isalpha(second_string[second_ptr]))
        {
            second_ptr++;
        }
    }
    return EQUAL;
}

//-------------------------------------------------------------------------------------------

void QSort(void* data, const size_t size, const size_t left, const size_t right,
           int (*Compare) (const void *, const void *))
{
    assert(data);
    assert(left <= right);

	if (left < right)
	{
        if (right - left == 1)
		{
			if ((*Compare)(data + left * size, data + right * size) != LESS)
			{
				Swap(data + right * size, data + left * size);
			}
		}
        else
        {
		    size_t mid = Partition(data, sizeof(char*), left, right, Compare);

		    QSort(data, size, left, mid, Compare);
		    QSort(data, size, mid + 1, right, Compare);
        }
	}
}

//-------------------------------------------------------------------------------------------

size_t Partition(void* data, const size_t size, const size_t left, const size_t right,
                 int (*Compare) (const void *, const void *))
{
    assert(data);
    assert(left <= right);

    void* mid = data + ((left + right) / 2) * size;

    size_t left_ptr  = left;
    size_t right_ptr = right;

    while (left_ptr <= right_ptr)
    {
        while ((*Compare)(data + left_ptr * size, mid) == LESS && right_ptr > left_ptr)
        {
            left_ptr++;
        }

        while ((*Compare)(data + right_ptr * size, mid) == MORE && right_ptr > left_ptr)
        {
            right_ptr--;
        }

		if (left_ptr >= right_ptr)
			break;

        Swap(data + left_ptr * size, data + right_ptr * size);

		left_ptr++;
		right_ptr--;
    }
    return right_ptr;
}



int ReverseCompare(const void* first_line, const void* second_line)
{
    assert(first_line);
    assert(second_line);

    const char* first_string  = *((const char**) first_line);
    const char* second_string = *((const char**) second_line);

    int first_ptr  = 0;
    int second_ptr = 0;

    while (first_string[first_ptr])   { first_ptr++; }
    while (second_string[second_ptr]) { second_ptr++; }

    first_ptr--;
    second_ptr--;

    while (first_string[first_ptr] != '\0' && second_string[second_ptr] != '\0')
    {
        if (isalpha(first_string[first_ptr]) && isalpha(second_string[second_ptr]))
        {
            int second = toupper(second_string[second_ptr--]);
            int first  = toupper(first_string[first_ptr--]);
            if (second == first)
                continue;
            else if (first < second)
                return LESS;
            else
                return MORE;
        }
        else if (!isalpha(first_string[first_ptr]))
        {
            first_ptr--;
        }
        else if (!isalpha(second_string[second_ptr]))
        {
            second_ptr--;
        }
    }
    return EQUAL;
}



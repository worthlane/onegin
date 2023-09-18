#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <assert.h>

#include "sorter.h"
#include "getoutinfo.h"
#include "test.h"

#define DEBUG

static const size_t buf_size = 64;

void Swap(void* ptr1, void* ptr2, size_t size)
{
    assert(ptr1);
    assert(ptr2);
    assert(ptr1 != ptr2);

    char buf[buf_size] = {};
    size_t steps = size / buf_size;
    size_t last  = size % buf_size;

    for (size_t i = 0; i < steps; i++)
    {
        memcpy(buf, ptr1, buf_size);
        assert(buf);

        memcpy(ptr1, ptr2, buf_size);
        assert(ptr1);

        memcpy(ptr2, buf, buf_size);
        assert(ptr2);
    }
    memcpy(buf, ptr1, last);
    assert(buf);

    memcpy(ptr1, ptr2, last);
    assert(ptr1);

    memcpy(ptr2, buf, last);
    assert(ptr2);
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

void QSort(const void* data, const size_t size, const size_t left, const size_t right,
           comparator_t* Compare)
{
    assert(data);
    assert(left <= right);

	if (left < right)
	{
        if (right - left == 1)
		{
			if (Compare(data + left * size, data + right * size) != LESS)
			{
				Swap((void*) data + right * size, (void*) data + left * size, size);
			}
		}
        else
        {
		    size_t mid = Partition(data, size, left, right, Compare);

		    QSort(data, size, left, mid, Compare);
		    QSort(data, size, mid + 1, right, Compare);
        }
	}
}

//-------------------------------------------------------------------------------------------

size_t Partition(const void* data, const size_t size, const size_t left, const size_t right,
                 comparator_t* Compare)
{
    assert(data);
    assert(left <= right);

    size_t mid_pos = (left + right) / 2;

    const void* mid = data + mid_pos * size;

    size_t left_ptr  = left;
    size_t right_ptr = right;

    while (left_ptr <= right_ptr)
    {
        while (Compare(data + left_ptr * size, mid) == LESS)
        {
            left_ptr++;
        }

        while (Compare(data + right_ptr * size, mid) == MORE)
        {
            right_ptr--;
        }

		if (left_ptr >= right_ptr)
			break;

        if (data + left_ptr * size == mid)
        {
            mid = data + right_ptr * size;
            mid_pos = right_ptr;
        }
        else if (data + right_ptr * size == mid)
        {
            mid = data + left_ptr * size;
            mid_pos = left_ptr;
        }

        Swap((void*) data + left_ptr * size, (void*) data + right_ptr * size, size);

		left_ptr++;
		right_ptr--;
    }
    return right_ptr;
}

//-------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------------

int AdressCompare(const void* first_adress, const void* second_adress)
{
    assert(first_adress);
    assert(second_adress);

    const long int A = *((const long int*) first_adress);
    const long int B = *((const long int*) second_adress);

    if (A > B)
        return MORE;
    else if (A < B)
        return LESS;

    return EQUAL;
}





#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <assert.h>

#include "sorter.h"
#include "input_and_output.h"
#include "test.h"

#define DEBUG

static const size_t buf_size = 64;

static size_t Partition(const void* data, const size_t size, const size_t left, const size_t right,
                 comparator_t* Compare);

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

    const struct LineInfo* first  = (const struct LineInfo*) first_line;
    const struct LineInfo* second = (const struct LineInfo*) second_line;

    int first_ptr  = 0;
    int second_ptr = 0;

    while ((first->string)[first_ptr] != '\0' && (second->string)[second_ptr] != '\0')
    {
        if (isalpha((first->string)[first_ptr]) && isalpha((second->string)[second_ptr]))
        {
            int second_symbol = toupper((second->string)[second_ptr++]);
            int first_symbol  = toupper((first->string)[first_ptr++]);
            if (second_symbol == first_symbol)
                continue;
            else if (first_symbol < second_symbol)
                return LESS;
            else
                return GREATER;
        }
        else if (!isalpha((first->string)[first_ptr]))
        {
            first_ptr++;
        }
        else if (!isalpha((second->string)[second_ptr]))
        {
            second_ptr++;
        }
    }

    if ((first->string)[first_ptr] - (second->string)[second_ptr] < 0)
    {
        return LESS;
    }
    else if ((first->string)[first_ptr] - (second->string)[second_ptr] > 0)
    {
        return GREATER;
    }

    return EQUAL;
}

//-------------------------------------------------------------------------------------------

void QSort(const void* info, const size_t size, const size_t left, const size_t right,
           comparator_t* Compare)
{
    assert(info);
    assert(left <= right);

    char* data = (char*) info;
    assert(data);

	if (left < right)
	{
        if (right - left == 1)
		{
			if (Compare(data + left * size, data + right * size) != LESS)
				Swap(data + right * size, data + left * size, size);
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

static size_t Partition(const void* info, const size_t size, const size_t left, const size_t right,
                 comparator_t* Compare)
{
    assert(info);


    assert(left <= right);

    char* data = (char*) info;
    assert(data);

    size_t mid_pos = (left + right) / 2;

    const void* mid = data + mid_pos * size;
    assert(mid);

    size_t left_ptr  = left;
    size_t right_ptr = right;

    while (left_ptr <= right_ptr)
    {
        while (Compare(data + left_ptr * size, mid) == LESS)
        {
            assert(left_ptr <= right_ptr);
            left_ptr++;
        }

        while (Compare(data + right_ptr * size, mid) == GREATER)
        {
            assert(left_ptr <= right_ptr);
            right_ptr--;
        }

		if (left_ptr >= right_ptr)
			break;

        if (data + left_ptr * size == mid)
        {
            mid = data + right_ptr * size;
        }
        else if (data + right_ptr * size == mid)
        {
            mid = data + left_ptr * size;
        }

        Swap(data + left_ptr * size, data + right_ptr * size, size);

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

    const struct LineInfo* first  = (const struct LineInfo*) first_line;
    const struct LineInfo* second = (const struct LineInfo*) second_line;

    int first_ptr  = first->len - 1;
    int second_ptr = second->len - 1;

    while ((first->string)[first_ptr] != '\0' && (second->string)[second_ptr] != '\0')
    {
        if (isalpha((first->string)[first_ptr]) && isalpha((second->string)[second_ptr]))
        {
            int second_symbol = toupper((second->string)[second_ptr--]);
            int first_symbol  = toupper((first->string)[first_ptr--]);
            if (second_symbol == first_symbol)
                continue;
            else if (first_symbol < second_symbol)
                return LESS;
            else
                return GREATER;
        }
        else if (!isalpha((first->string)[first_ptr]))
        {
            first_ptr--;
        }
        else if (!isalpha((second->string)[second_ptr]))
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
        return GREATER;
    else if (A < B)
        return LESS;

    return EQUAL;
}





#include <assert.h>

#include "sorter.h"
#include "mylib/colorlib.h"
#include "test.h"

#define TEST_LEN 15

void TestQSort()
{
    int origin[TEST_LEN] = {4, 2, 7, 8, 10, 5, 11, 228, 18, 9, 13, 100, 1, 110, 17};
    int data[TEST_LEN] = {4, 2, 7, 8, 10, 5, 11, 228, 18, 9, 13, 100, 1, 110, 17};

    qsort(origin, TEST_LEN, sizeof(int), &CompareInt);

    QSort(data, sizeof(int), 0, TEST_LEN - 1, &CompareInt);

    for (size_t i = 0; i < TEST_LEN; i++)
    {
        if (origin[i] != data[i])
        {
            PrintRedText(stderr, "TEST ERROR IN TESTQSORT\n", "");
            PrintRedText(stderr, "EXPECTED\n", "");
            PrintArray(origin, TEST_LEN);
            PrintRedText(stderr, "FUNCTION\n", "");
            PrintArray(data, TEST_LEN);
            return;
        }
    }

    PrintGreenText(stderr, "TEST RAN SUCCESSFULLY", "");
}

//-------------------------------------------------------------------------------------------

int CompareInt(const void* a, const void* b)
{
    assert(a);
    assert(b);

    const int A = *((const int*) a);
    const int B = *((const int*) b);

    if (A > B)
        return GREATER;
    else if (A < B)
        return LESS;

    return EQUAL;
}

//-------------------------------------------------------------------------------------------

void PrintArray(const int data[], const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        PrintMagentaText(stdout, "%d, ", data[i]);
    }
    putchar('\n');
}

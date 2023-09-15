#ifndef __TEST_H
#define __TEST_H

/*! \file
* \brief info about test mode functions
*/

/************************************************************//**
 * @brief Compares two numbers
 *
 * @param[in] a first number
 * @param[in] b second number
 * @return -1 if a < b
 * @return 0 if a = b
 * @return 1 if a > b
 ***********************************************************/

int CompareInt(const void* a, const void* b);

/************************************************************//**
 * @brief Prints array of numbers
 *
 * @param[in] data array
 * @param[in] size size of array
 ***********************************************************/

void PrintArray(const int data[], const size_t size);

/************************************************************//**
 * @brief Runs QSort test
 ************************************************************/

void TestQSort();

#endif

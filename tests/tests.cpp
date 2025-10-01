#include <gtest/gtest.h>
#include "../header.h"

TEST(ArrayOperationsTest, FindMinMaxValues)
{
    ArrayValue arr(9);
    int testArr[] = {0, 5000, -1, 2718, -1, 5000, 0, 0, 0};
    for (int i = 0; i < 9; i++) arr.array[i] = testArr[i];

    findMinMax(&arr);
    EXPECT_EQ(arr.min, -1);
    EXPECT_EQ(arr.max, 5000);
}

TEST(ArrayOperationsTest, CalculateAverageValue)
{
    ArrayValue arr(5);
    int testArr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) arr.array[i] = testArr[i];

    calculateAverage(&arr);
    EXPECT_DOUBLE_EQ(arr.averageValue, 3);
}
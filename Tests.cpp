//
// Created by korna on 20.03.2021.
//
#include "gtest/gtest.h"
#include "DynamicArray.cpp"

TEST(Dynamic_array_primitive, PositiveNos) {
    DynamicArray<int> arr = DynamicArray<int>();
    ASSERT_EQ (0, arr.GetLength());
    arr.Resize(1);
    ASSERT_EQ (1, arr.GetLength());
    arr[0] = 5;
    EXPECT_EQ (5, arr[0]);
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
}

TEST(Dynamic_array_set_from_arr, PositiveNos) {
    int a[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr = DynamicArray<int>(a, 5);
    EXPECT_EQ (0, arr.GetLength());
    arr.Resize(1);
    EXPECT_EQ (1, arr.GetLength());
    arr[0] = 5;
    EXPECT_EQ (5, arr[0]);
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
}

TEST(Dynamic_array_copy, PositiveNos) {
    int a[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr = DynamicArray<int>(a, 5);
    EXPECT_EQ (0, arr.GetLength());
    arr.Resize(1);
    EXPECT_EQ (1, arr.GetLength());
    arr[0] = 5;
    EXPECT_EQ (5, arr[0]);
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
}

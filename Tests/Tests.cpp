////
//// Created by korna on 20.03.2021.
////
#include "gtest/gtest.h"
#include "../DynamicArray.cpp"
#include "../LinkedList.cpp"

TEST(DynamicArray, Basic) {
    DynamicArray<int> arr = DynamicArray<int>();
    ASSERT_EQ (0, arr.GetLength());
    EXPECT_ANY_THROW(arr.Resize(-1));
    arr.Resize(1);
    ASSERT_EQ (1, arr.GetLength());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);

    arr[0] = 5;
    EXPECT_EQ (5, arr[0]);
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);

    EXPECT_ANY_THROW(DynamicArray<int>(-1));
    DynamicArray<int> arr1 = DynamicArray<int>(2);
    ASSERT_EQ (2, arr1.GetLength());
    arr1[0] = 1;
    EXPECT_EQ (1, arr1[0]);
    EXPECT_EQ (0, arr1[1]);
}

TEST(DynamicArray, SetFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(DynamicArray<int>(a, -1));
    EXPECT_ANY_THROW(DynamicArray<int>(nullptr, 1));
    DynamicArray<int> arr = DynamicArray<int>(a, 5);
    ASSERT_EQ (5, arr.GetLength());
    arr.Resize(6);
    ASSERT_EQ (6, arr.GetLength());

    arr[5] = 6;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr.Resize(5);
    EXPECT_ANY_THROW(arr[5]);
    ASSERT_EQ (5, arr.GetLength());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
}

TEST(DynamicArray, Copy) {
    int a[] = {1, 2, 3, 4, 5, 6};
    DynamicArray<int> arr1 = DynamicArray<int>(a, 5);
    ASSERT_EQ (5, arr1.GetLength());
    EXPECT_ANY_THROW(arr1[5]);
    DynamicArray<int> arr2 = DynamicArray<int>(arr1);
    ASSERT_EQ (5, arr2.GetLength());
    EXPECT_EQ (arr1[0], arr2[0]);
    EXPECT_EQ (arr1[1], arr2[1]);
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr1.Set(0, 2);
    EXPECT_EQ (arr1[0], 2);
    EXPECT_EQ (arr2[0], 1);
    arr2.Resize(arr2.GetLength() + 1);
    ASSERT_EQ (5, arr1.GetLength());
    ASSERT_EQ (6, arr2.GetLength());
}


TEST(LinkedList, Basic) {
    LinkedList<int> arr = LinkedList<int>();
    ASSERT_EQ(0, arr.GetLength());
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW(arr.GetLast());

    arr.Append(5);
    ASSERT_EQ (1, arr.GetLength());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Append(5);
    ASSERT_EQ (2, arr.GetLength());
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.Prepend(3);
    ASSERT_EQ (3, arr.GetLength());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (5, arr[2]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.InsertAt(4, 1);
    ASSERT_EQ (4, arr.GetLength());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (1, arr[2]);
    EXPECT_EQ (5, arr[3]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    EXPECT_ANY_THROW(arr.RemoveAt(-1));
    EXPECT_ANY_THROW(arr.RemoveAt(4));
    arr.RemoveAt(1);
    ASSERT_EQ (3, arr.GetLength());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (5, arr[2]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.PopFirst();
    ASSERT_EQ (2, arr.GetLength());
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.PopLast();
    ASSERT_EQ (1, arr.GetLength());
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());

    arr.PopLast();
    ASSERT_EQ (0, arr.GetLength());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
    EXPECT_ANY_THROW(arr.PopFirst());
    EXPECT_ANY_THROW(arr.RemoveAt(0));


    EXPECT_ANY_THROW(LinkedList<int>(-1));
    LinkedList<int> arr1 = LinkedList<int>(2);
    ASSERT_EQ (2, arr1.GetLength());
    arr1[0] = 1;
    EXPECT_EQ (1, arr1[0]);
    EXPECT_EQ (0, arr1[1]);
    EXPECT_EQ (1, arr1.GetFirst());
    EXPECT_EQ (0, arr1.GetLast());
}

TEST(LinkedList, SetFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(LinkedList<int>(a, -1));
    EXPECT_ANY_THROW(LinkedList<int>(nullptr, 1));
    LinkedList<int> arr = LinkedList<int>(a, 5);
    ASSERT_EQ (5, arr.GetLength());

    arr.Append(6);
    ASSERT_EQ (6, arr.GetLength());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr.PopLast();
    EXPECT_ANY_THROW(arr[5]);
    ASSERT_EQ (5, arr.GetLength());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
}

TEST(LinkedList, Copy) {
    int a[] = {1, 2, 3, 4, 5, 6};
    LinkedList<int> arr1 = LinkedList<int>(a, 5);
    ASSERT_EQ (5, arr1.GetLength());
    EXPECT_ANY_THROW(arr1[5]);
    LinkedList<int> arr2 = LinkedList<int>(arr1);
    ASSERT_EQ (5, arr2.GetLength());
    EXPECT_EQ (arr1[0], arr2[0]);
    EXPECT_EQ (arr1[1], arr2[1]);
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr1.Set(0, 2);
    EXPECT_EQ (arr1[0], 2);
    EXPECT_EQ (arr2[0], 1);
    arr2.Append(0);
    ASSERT_EQ (5, arr1.GetLength());
    ASSERT_EQ (6, arr2.GetLength());
}

TEST(LinkedList, Advanced) {
    int a[] = {1, 2, 3, 4, 5};
    LinkedList<int> arr1 = LinkedList<int>(a, 5);
    LinkedList<int> arr2 = LinkedList<int>(arr1);
    LinkedList<int> arr3 = arr1.Concat(arr2);
    ASSERT_EQ (arr1.GetLength() + arr2.GetLength(), arr3.GetLength());
    EXPECT_EQ (arr1[0], arr3[0]);
    EXPECT_EQ (arr1[1], arr3[1]);
    EXPECT_EQ (arr1[2], arr3[2]);
    EXPECT_EQ (arr1[3], arr3[3]);
    EXPECT_EQ (arr1[4], arr3[4]);
    EXPECT_EQ (arr2[0], arr3[5]);
    EXPECT_EQ (arr2[1], arr3[6]);
    EXPECT_EQ (arr2[2], arr3[7]);
    EXPECT_EQ (arr2[3], arr3[8]);
    EXPECT_EQ (arr2[4], arr3[9]);

    LinkedList<int> arr4 = LinkedList<int>();
    arr3 = arr1.Concat(arr4);
    ASSERT_EQ (arr1.GetLength() + arr4.GetLength(), arr3.GetLength());
    EXPECT_EQ (arr1[0], arr3[0]);
    EXPECT_EQ (arr1[1], arr3[1]);
    EXPECT_EQ (arr1[2], arr3[2]);
    EXPECT_EQ (arr1[3], arr3[3]);
    EXPECT_EQ (arr1[4], arr3[4]);

    arr1 = arr3.GetSubList(0, 0);
    ASSERT_EQ(arr1.GetLength(), 1);
    EXPECT_EQ (arr1[0], 1);
    EXPECT_ANY_THROW(arr1[1]);
    EXPECT_ANY_THROW(arr3.GetSubList(-1, 0));
    EXPECT_ANY_THROW(arr3.GetSubList(1, 0));
    EXPECT_ANY_THROW(arr3.GetSubList(1, 5));

    arr1 = arr3.GetSubList(0, 4);
    ASSERT_EQ(arr1.GetLength(), 5);
    EXPECT_EQ (arr1[0], arr3[0]);
    EXPECT_EQ (arr1[1], arr3[1]);
    EXPECT_EQ (arr1[2], arr3[2]);
    EXPECT_EQ (arr1[3], arr3[3]);
    EXPECT_EQ (arr1[4], arr3[4]);

    arr1 = arr3.GetSubList(2, 3);
    ASSERT_EQ(arr1.GetLength(), 2);
    EXPECT_EQ (arr1[0], arr3[2]);
    EXPECT_EQ (arr1[1], arr3[3]);
}
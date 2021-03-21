////
//// Created by korna on 20.03.2021.
////
#include "gtest/gtest.h"
#include "DynamicArray.cpp"
#include "LinkedList.cpp"

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

    arr.RemoveFirst();
    ASSERT_EQ (2, arr.GetLength());
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.RemoveLast();
    ASSERT_EQ (1, arr.GetLength());
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());

    arr.RemoveLast();
    ASSERT_EQ (0, arr.GetLength());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveFirst());
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

    arr.RemoveLast();
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

}

TEST(LinkedList, Advanced) {
}
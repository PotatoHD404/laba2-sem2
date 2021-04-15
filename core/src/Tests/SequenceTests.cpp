////
//// Created by korna on 22.03.2021.
////
//#include "gtest/gtest.h"
//#include "../ListSequence.h"
//#include "../ArraySequence.h"
//
//TEST(Sequence, ListSequence_InitDefault) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>(new ListSequence<int>());
//    ASSERT_EQ(0, arr->GetLength());
//    EXPECT_ANY_THROW(arr->GetFirst());
//    EXPECT_ANY_THROW(arr->GetLast());
//}
//
//TEST(Sequence, ListSequence_InitCount_Set) {
//    EXPECT_ANY_THROW(ListSequence<int>(-1));
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>(2));
//    ASSERT_EQ (2, arr->GetLength());
//    arr->At(0) = 1;
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (0, arr->At(1));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (0, arr->GetLast());
//    arr = unique_ptr<Sequence<int>>(new ListSequence<int>(0));
//    ASSERT_EQ (0, arr->GetLength());
//}
//
//
//TEST(Sequence, ListSequence_Append) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>());
//    arr->Append(5);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_ANY_THROW(arr->At(-1));
//    EXPECT_ANY_THROW(arr->At(1));
//    EXPECT_EQ (5, arr->At(0));
//
//    arr->At(0) = 4;
//    EXPECT_EQ (4, arr->At(0));
//    EXPECT_EQ (4, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//    EXPECT_ANY_THROW(arr->Set(-1, 1));
//    EXPECT_ANY_THROW(arr->Set(1, 1));
//
//    arr->Append(5);
//    ASSERT_EQ (2, arr->GetLength());
//    arr->Set(0, 1);
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (5, arr->At(1));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (5, arr->GetLast());
//
//    arr->Append(3);
//    ASSERT_EQ (3, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (5, arr->At(1));
//    EXPECT_EQ (3, arr->At(2));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//}
//
//TEST(Sequence, ListSequence_Prepend) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>());
//    arr->Prepend(5);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_ANY_THROW(arr->At(-1));
//    EXPECT_ANY_THROW(arr->At(1));
//    EXPECT_EQ (5, arr->At(0));
//
//    arr->At(0) = 4;
//    EXPECT_EQ (4, arr->At(0));
//    EXPECT_EQ (4, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//    EXPECT_ANY_THROW(arr->Set(-1, 1));
//    EXPECT_ANY_THROW(arr->Set(1, 1));
//
//    arr->Prepend(5);
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (5, arr->At(0));
//    EXPECT_EQ (4, arr->At(1));
//    EXPECT_EQ (5, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//
//    arr->Prepend(3);
//    ASSERT_EQ (3, arr->GetLength());
//    EXPECT_EQ (3, arr->At(0));
//    EXPECT_EQ (5, arr->At(1));
//    EXPECT_EQ (4, arr->At(2));
//    EXPECT_EQ (3, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//}
//
//TEST(Sequence, ListSequence_InsertAt) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    arr->InsertAt(4, 1);
//    ASSERT_EQ (4, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (4, arr->At(1));
//    EXPECT_EQ (2, arr->At(2));
//    EXPECT_EQ (3, arr->At(3));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->InsertAt(5, 0);
//    ASSERT_EQ (5, arr->GetLength());
//    EXPECT_EQ (5, arr->At(0));
//    EXPECT_EQ (1, arr->At(1));
//    EXPECT_EQ (4, arr->At(2));
//    EXPECT_EQ (2, arr->At(3));
//    EXPECT_EQ (3, arr->At(4));
//    EXPECT_EQ (5, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->InsertAt(6, arr->GetLength() - 1);
//    ASSERT_EQ (6, arr->GetLength());
//    EXPECT_EQ (5, arr->At(0));
//    EXPECT_EQ (1, arr->At(1));
//    EXPECT_EQ (4, arr->At(2));
//    EXPECT_EQ (2, arr->At(3));
//    EXPECT_EQ (3, arr->At(4));
//    EXPECT_EQ (6, arr->At(5));
//    EXPECT_EQ (5, arr->GetFirst());
//    EXPECT_EQ (6, arr->GetLast());
//}
//
//TEST(Sequence, ListSequence_PopFirst) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    arr->PopFirst();
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (2, arr->At(0));
//    EXPECT_EQ (3, arr->At(1));
//    EXPECT_EQ (2, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->PopFirst();
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (3, arr->At(0));
//    EXPECT_EQ (3, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->PopFirst();
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW(arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW (arr->PopFirst(););
//}
//
//TEST(Sequence, ListSequence_PopLast) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    arr->PopLast();
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (2, arr->At(1));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (2, arr->GetLast());
//
//    arr->PopLast();
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (1, arr->GetLast());
//
//    arr->PopLast();
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW (arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW(arr->PopLast());
//}
//
//TEST(Sequence, ListSequence_RemoveAt) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    ASSERT_ANY_THROW(arr->RemoveAt(-1));
//    ASSERT_ANY_THROW(arr->RemoveAt(3));
//    arr->RemoveAt(1);
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (3, arr->At(1));
//    ASSERT_ANY_THROW (arr->At(2));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->RemoveAt(0);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (3, arr->At(0));
//    EXPECT_EQ (3, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->RemoveAt(0);
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW (arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW(arr->PopLast());
//    EXPECT_ANY_THROW(arr->RemoveAt(0));
//
//    arr = unique_ptr<Sequence<int>>(new ListSequence<int>(2));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//
//    arr->RemoveAt(1);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (1, arr->GetLast());
//
//    arr->RemoveAt(0);
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW (arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW(arr->PopLast());
//    EXPECT_ANY_THROW(arr->RemoveAt(0));
//}
//
//TEST(Sequence, ListSequence_InitFromArr) {
//    int a[] = {1, 2, 3, 4, 5};
//    EXPECT_ANY_THROW(ListSequence<int>(a, -1));
//    EXPECT_ANY_THROW(ListSequence<int>(nullptr, 1));
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ListSequence<int>(a, 5));
//    ASSERT_EQ (5, arr->GetLength());
//
//    arr->Append(6);
//    ASSERT_EQ (6, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (2, arr->At(1));
//    EXPECT_EQ (3, arr->At(2));
//    EXPECT_EQ (4, arr->At(3));
//    EXPECT_EQ (5, arr->At(4));
//    EXPECT_EQ (6, arr->At(5));
//
//    arr->PopLast();
//    EXPECT_ANY_THROW(arr->At(5));
//    ASSERT_EQ (5, arr->GetLength());
//    arr->Set(0, 1);
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (2, arr->At(1));
//    EXPECT_EQ (3, arr->At(2));
//    EXPECT_EQ (4, arr->At(3));
//    EXPECT_EQ (5, arr->At(4));
//    arr = unique_ptr<Sequence<int>>(new ListSequence<int>(a, 0));
//    ASSERT_EQ (0, arr->GetLength());
//}
//
//TEST(Sequence, ListSequence_InitFromListSequence) {
//    int a[] = {1, 2, 3, 4, 5, 6};
//    unique_ptr<Sequence<int>> arr1 = unique_ptr<Sequence<int>>(new ListSequence<int>(a, 5));
//    ASSERT_EQ (5, arr1->GetLength());
//    EXPECT_ANY_THROW(arr1->At(5));
//    unique_ptr<Sequence<int>> arr2 = unique_ptr<Sequence<int>>(new ListSequence<int>(*(arr1.get())));
//    ASSERT_EQ (5, arr2->GetLength());
//    EXPECT_EQ (arr1->At(0), arr2->At(0));
//    EXPECT_EQ (arr1->At(1), arr2->At(1));
//    EXPECT_EQ (arr1->At(2), arr2->At(2));
//    EXPECT_EQ (arr1->At(3), arr2->At(3));
//    EXPECT_EQ (arr1->At(4), arr2->At(4));
//
//    arr1->Set(0, 2);
//    EXPECT_EQ (arr1->At(0), 2);
//    EXPECT_EQ (arr2->At(0), 1);
//    arr2->Append(0);
//    ASSERT_EQ (5, arr1->GetLength());
//    ASSERT_EQ (6, arr2->GetLength());
//
//    arr1 = unique_ptr<Sequence<int>>(new ListSequence<int>());
//    arr2 = unique_ptr<Sequence<int>>(new ListSequence<int>(arr1));
//    ASSERT_EQ (0, arr2->GetLength());
//}
//
//TEST(Sequence, ListSequence_Concat) {
//    int a[] = {1, 2, 3, 4, 5};
//    unique_ptr<Sequence<int>> arr1 = unique_ptr<Sequence<int>>(new ListSequence<int>(a, 5));
//    unique_ptr<Sequence<int>> arr2 = unique_ptr<Sequence<int>>(new ListSequence<int>(arr1));
//    unique_ptr<Sequence<int>> arr3 = unique_ptr<Sequence<int>>(arr1->Concat(arr2));
//    ASSERT_EQ (arr1->GetLength() + arr2->GetLength(), arr3->GetLength());
//    EXPECT_EQ (arr1->At(0), arr3->At(0));
//    EXPECT_EQ (arr1->At(1), arr3->At(1));
//    EXPECT_EQ (arr1->At(2), arr3->At(2));
//    EXPECT_EQ (arr1->At(3), arr3->At(3));
//    EXPECT_EQ (arr1->At(4), arr3->At(4));
//    EXPECT_EQ (arr2->At(0), arr3->At(5));
//    EXPECT_EQ (arr2->At(1), arr3->At(6));
//    EXPECT_EQ (arr2->At(2), arr3->At(7));
//    EXPECT_EQ (arr2->At(3), arr3->At(8));
//    EXPECT_EQ (arr2->At(4), arr3->At(9));
//
//    unique_ptr<Sequence<int>> arr4 = unique_ptr<Sequence<int>>(new ListSequence<int>());
//    arr3 = unique_ptr<Sequence<int>>(arr1->Concat(arr4));
//    ASSERT_EQ (arr1->GetLength() + arr4->GetLength(), arr3->GetLength());
//    EXPECT_EQ (arr1->At(0), arr3->At(0));
//    EXPECT_EQ (arr1->At(1), arr3->At(1));
//    EXPECT_EQ (arr1->At(2), arr3->At(2));
//    EXPECT_EQ (arr1->At(3), arr3->At(3));
//    EXPECT_EQ (arr1->At(4), arr3->At(4));
//}
//
//TEST(Sequence, ListSequence_Subsequence) {
//    int a[] = {1, 2, 3, 4, 5};
//    unique_ptr<Sequence<int>> arr1 = uniquea_ptr<Sequence<int>>(new ListSequence<int>(a, 5));
//    unique_ptr<Sequence<int>>
//            arr2 = unique_ptr<Sequence<int>>(arr1->Subsequence(0, 0));
//    ASSERT_EQ(arr2->GetLength(), 1);
//    EXPECT_EQ (arr1->At(0), 1);
//    EXPECT_ANY_THROW(arr2->At(1));
//    EXPECT_ANY_THROW(arr1->Subsequence(-1, 0));
//    EXPECT_ANY_THROW(arr1->Subsequence(1, 0));
//    EXPECT_ANY_THROW(arr1->Subsequence(1, 5));
//    arr2 = unique_ptr<Sequence<int>>(arr1->Subsequence(0, 4));
//    ASSERT_EQ(arr2->GetLength(), 5);
//    EXPECT_EQ (arr1->At(0), arr2->At(0));
//    EXPECT_EQ (arr1->At(1), arr2->At(1));
//    EXPECT_EQ (arr1->At(2), arr2->At(2));
//    EXPECT_EQ (arr1->At(3), arr2->At(3));
//    EXPECT_EQ (arr1->At(4), arr2->At(4));
//    arr2 = unique_ptr<Sequence<int>>(arr1->Subsequence(2, 3));
//    ASSERT_EQ(arr2->GetLength(), 2);
//    EXPECT_EQ (arr1->At(2), arr2->At(0));
//    EXPECT_EQ (arr1->At(3), arr2->At(1));
//}
//
//TEST(Sequence, ArraySequence_InitDefault) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>(new ArraySequence<int>());
//    ASSERT_EQ(0, arr->GetLength());
//    EXPECT_ANY_THROW(arr->GetFirst());
//    EXPECT_ANY_THROW(arr->GetLast());
//}
//
//TEST(Sequence, ArraySequence_InitCount_Set) {
//    EXPECT_ANY_THROW(ArraySequence<int>(-1));
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>(2));
//    ASSERT_EQ (2, arr->GetLength());
//    arr->At(0) = 1;
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (0, arr->At(1));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (0, arr->GetLast());
//    arr = unique_ptr<Sequence<int>>(new ArraySequence<int>(0));
//    ASSERT_EQ (0, arr->GetLength());
//}
//
//
//TEST(Sequence, ArraySequence_Append) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>());
//    arr->Append(5);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_ANY_THROW(arr->At(-1));
//    EXPECT_ANY_THROW(arr->At(1));
//    EXPECT_EQ (5, arr->At(0));
//
//    arr->At(0) = 4;
//    EXPECT_EQ (4, arr->At(0));
//    EXPECT_EQ (4, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//    EXPECT_ANY_THROW(arr->Set(-1, 1));
//    EXPECT_ANY_THROW(arr->Set(1, 1));
//
//    arr->Append(5);
//    ASSERT_EQ (2, arr->GetLength());
//    arr->Set(0, 1);
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (5, arr->At(1));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (5, arr->GetLast());
//
//    arr->Append(3);
//    ASSERT_EQ (3, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (5, arr->At(1));
//    EXPECT_EQ (3, arr->At(2));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//}
//
//TEST(Sequence, ArraySequence_Prepend) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>());
//    arr->Prepend(5);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_ANY_THROW(arr->At(-1));
//    EXPECT_ANY_THROW(arr->At(1));
//    EXPECT_EQ (5, arr->At(0));
//
//    arr->At(0) = 4;
//    EXPECT_EQ (4, arr->At(0));
//    EXPECT_EQ (4, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//    EXPECT_ANY_THROW(arr->Set(-1, 1));
//    EXPECT_ANY_THROW(arr->Set(1, 1));
//
//    arr->Prepend(5);
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (5, arr->At(0));
//    EXPECT_EQ (4, arr->At(1));
//    EXPECT_EQ (5, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//
//    arr->Prepend(3);
//    ASSERT_EQ (3, arr->GetLength());
//    EXPECT_EQ (3, arr->At(0));
//    EXPECT_EQ (5, arr->At(1));
//    EXPECT_EQ (4, arr->At(2));
//    EXPECT_EQ (3, arr->GetFirst());
//    EXPECT_EQ (4, arr->GetLast());
//}
//
//TEST(Sequence, ArraySequence_InsertAt) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    arr->InsertAt(4, 1);
//    ASSERT_EQ (4, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (4, arr->At(1));
//    EXPECT_EQ (2, arr->At(2));
//    EXPECT_EQ (3, arr->At(3));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->InsertAt(5, 0);
//    ASSERT_EQ (5, arr->GetLength());
//    EXPECT_EQ (5, arr->At(0));
//    EXPECT_EQ (1, arr->At(1));
//    EXPECT_EQ (4, arr->At(2));
//    EXPECT_EQ (2, arr->At(3));
//    EXPECT_EQ (3, arr->At(4));
//    EXPECT_EQ (5, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->InsertAt(6, arr->GetLength() - 1);
//    ASSERT_EQ (6, arr->GetLength());
//    EXPECT_EQ (5, arr->At(0));
//    EXPECT_EQ (1, arr->At(1));
//    EXPECT_EQ (4, arr->At(2));
//    EXPECT_EQ (2, arr->At(3));
//    EXPECT_EQ (3, arr->At(4));
//    EXPECT_EQ (6, arr->At(5));
//    EXPECT_EQ (5, arr->GetFirst());
//    EXPECT_EQ (6, arr->GetLast());
//}
//
//TEST(Sequence, ArraySequence_PopFirst) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    arr->PopFirst();
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (2, arr->At(0));
//    EXPECT_EQ (3, arr->At(1));
//    EXPECT_EQ (2, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->PopFirst();
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (3, arr->At(0));
//    EXPECT_EQ (3, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->PopFirst();
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW(arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW (arr->PopFirst(););
//}
//
//TEST(Sequence, ArraySequence_PopLast) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    arr->PopLast();
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (2, arr->At(1));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (2, arr->GetLast());
//
//    arr->PopLast();
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (1, arr->GetLast());
//
//    arr->PopLast();
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW (arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW(arr->PopLast());
//}
//
//TEST(Sequence, ArraySequence_RemoveAt) {
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>(3));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//    arr->At(2) = 3;
//    ASSERT_ANY_THROW(arr->RemoveAt(-1));
//    ASSERT_ANY_THROW(arr->RemoveAt(3));
//    arr->RemoveAt(1);
//    ASSERT_EQ (2, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (3, arr->At(1));
//    ASSERT_ANY_THROW (arr->At(2));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->RemoveAt(0);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (3, arr->At(0));
//    EXPECT_EQ (3, arr->GetFirst());
//    EXPECT_EQ (3, arr->GetLast());
//
//    arr->RemoveAt(0);
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW (arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW(arr->PopLast());
//    EXPECT_ANY_THROW(arr->RemoveAt(0));
//
//    arr = unique_ptr<Sequence<int>>(new ArraySequence<int>(2));
//    arr->At(0) = 1;
//    arr->At(1) = 2;
//
//    arr->RemoveAt(1);
//    ASSERT_EQ (1, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (1, arr->GetFirst());
//    EXPECT_EQ (1, arr->GetLast());
//
//    arr->RemoveAt(0);
//    ASSERT_EQ (0, arr->GetLength());
//    EXPECT_ANY_THROW (arr->At(0));
//    EXPECT_ANY_THROW (arr->GetFirst());
//    EXPECT_ANY_THROW (arr->GetLast());
//    EXPECT_ANY_THROW(arr->PopLast());
//    EXPECT_ANY_THROW(arr->RemoveAt(0));
//}
//
//TEST(Sequence, ArraySequence_InitFromArr) {
//    int a[] = {1, 2, 3, 4, 5};
//    EXPECT_ANY_THROW(ArraySequence<int>(a, -1));
//    EXPECT_ANY_THROW(ArraySequence<int>(nullptr, 1));
//    unique_ptr<Sequence<int>> arr = unique_ptr<Sequence<int>>( new ArraySequence<int>(a, 5));
//    ASSERT_EQ (5, arr->GetLength());
//
//    arr->Append(6);
//    ASSERT_EQ (6, arr->GetLength());
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (2, arr->At(1));
//    EXPECT_EQ (3, arr->At(2));
//    EXPECT_EQ (4, arr->At(3));
//    EXPECT_EQ (5, arr->At(4));
//    EXPECT_EQ (6, arr->At(5));
//
//    arr->PopLast();
//    EXPECT_ANY_THROW(arr->At(5));
//    ASSERT_EQ (5, arr->GetLength());
//    arr->Set(0, 1);
//    EXPECT_EQ (1, arr->At(0));
//    EXPECT_EQ (2, arr->At(1));
//    EXPECT_EQ (3, arr->At(2));
//    EXPECT_EQ (4, arr->At(3));
//    EXPECT_EQ (5, arr->At(4));
//    arr = unique_ptr<Sequence<int>>(new ArraySequence<int>(a, 0));
//    ASSERT_EQ (0, arr->GetLength());
//}
//
//TEST(Sequence, ArraySequence_InitFromArraySequence) {
//    int a[] = {1, 2, 3, 4, 5, 6};
//    unique_ptr<Sequence<int>> arr1 = unique_ptr<Sequence<int>>(new ArraySequence<int>(a, 5));
//    ASSERT_EQ (5, arr1->GetLength());
//    EXPECT_ANY_THROW(arr1->At(5));
//    unique_ptr<Sequence<int>> arr2 = unique_ptr<Sequence<int>>(new ArraySequence<int>(*(arr1.get())));
//    ASSERT_EQ (5, arr2->GetLength());
//    EXPECT_EQ (arr1->At(0), arr2->At(0));
//    EXPECT_EQ (arr1->At(1), arr2->At(1));
//    EXPECT_EQ (arr1->At(2), arr2->At(2));
//    EXPECT_EQ (arr1->At(3), arr2->At(3));
//    EXPECT_EQ (arr1->At(4), arr2->At(4));
//
//    arr1->Set(0, 2);
//    EXPECT_EQ (arr1->At(0), 2);
//    EXPECT_EQ (arr2->At(0), 1);
//    arr2->Append(0);
//    ASSERT_EQ (5, arr1->GetLength());
//    ASSERT_EQ (6, arr2->GetLength());
//
//    arr1 = unique_ptr<Sequence<int>>(new ArraySequence<int>());
//    arr2 = unique_ptr<Sequence<int>>(new ArraySequence<int>(arr1));
//    ASSERT_EQ (0, arr2->GetLength());
//}
//
//TEST(Sequence, ArraySequence_Concat) {
//    int a[] = {1, 2, 3, 4, 5};
//    unique_ptr<Sequence<int>> arr1 = unique_ptr<Sequence<int>>(new ArraySequence<int>(a, 5));
//    unique_ptr<Sequence<int>> arr2 = unique_ptr<Sequence<int>>(new ArraySequence<int>(arr1));
//    unique_ptr<Sequence<int>> arr3 = unique_ptr<Sequence<int>>(arr1->Concat(arr2));
//    ASSERT_EQ (arr1->GetLength() + arr2->GetLength(), arr3->GetLength());
//    EXPECT_EQ (arr1->At(0), arr3->At(0));
//    EXPECT_EQ (arr1->At(1), arr3->At(1));
//    EXPECT_EQ (arr1->At(2), arr3->At(2));
//    EXPECT_EQ (arr1->At(3), arr3->At(3));
//    EXPECT_EQ (arr1->At(4), arr3->At(4));
//    EXPECT_EQ (arr2->At(0), arr3->At(5));
//    EXPECT_EQ (arr2->At(1), arr3->At(6));
//    EXPECT_EQ (arr2->At(2), arr3->At(7));
//    EXPECT_EQ (arr2->At(3), arr3->At(8));
//    EXPECT_EQ (arr2->At(4), arr3->At(9));
//
//    unique_ptr<Sequence<int>> arr4 = unique_ptr<Sequence<int>>(new ArraySequence<int>());
//    arr3 = unique_ptr<Sequence<int>>(arr1->Concat(arr4));
//    ASSERT_EQ (arr1->GetLength() + arr4->GetLength(), arr3->GetLength());
//    EXPECT_EQ (arr1->At(0), arr3->At(0));
//    EXPECT_EQ (arr1->At(1), arr3->At(1));
//    EXPECT_EQ (arr1->At(2), arr3->At(2));
//    EXPECT_EQ (arr1->At(3), arr3->At(3));
//    EXPECT_EQ (arr1->At(4), arr3->At(4));
//}
//
//TEST(Sequence, ArraySequence_Subsequence) {
//    int a[] = {1, 2, 3, 4, 5};
//    unique_ptr<Sequence<int>> arr1 = unique_ptr<Sequence<int>>(new ArraySequence<int>(a, 5));
//    unique_ptr<Sequence<int>>
//            arr2 = unique_ptr<Sequence<int>>(arr1->Subsequence(0, 0));
//    ASSERT_EQ(arr2->GetLength(), 1);
//    EXPECT_EQ (arr1->At(0), 1);
//    EXPECT_ANY_THROW(arr2->At(1));
//    EXPECT_ANY_THROW(arr1->Subsequence(-1, 0));
//    EXPECT_ANY_THROW(arr1->Subsequence(1, 0));
//    EXPECT_ANY_THROW(arr1->Subsequence(1, 5));
//    arr2 = unique_ptr<Sequence<int>>(arr1->Subsequence(0, 4));
//    ASSERT_EQ(arr2->GetLength(), 5);
//    EXPECT_EQ (arr1->At(0), arr2->At(0));
//    EXPECT_EQ (arr1->At(1), arr2->At(1));
//    EXPECT_EQ (arr1->At(2), arr2->At(2));
//    EXPECT_EQ (arr1->At(3), arr2->At(3));
//    EXPECT_EQ (arr1->At(4), arr2->At(4));
//    arr2 = unique_ptr<Sequence<int>>(arr1->Subsequence(2, 3));
//    ASSERT_EQ(arr2->GetLength(), 2);
//    EXPECT_EQ (arr1->At(2), arr2->At(0));
//    EXPECT_EQ (arr1->At(3), arr2->At(1));
//}
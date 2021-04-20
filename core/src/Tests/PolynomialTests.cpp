//
// Created by korna on 20.04.2021.
//
#include "gtest/gtest.h"
#include <iostream>
#include "../Polynomial.h"

using namespace std;

TEST(Polynomial, Sum) {
    Polynomial<int> poly1 = {1, 2, 1};
    Polynomial<int> poly2 = {1, 2, 3, 4, 5};
    poly2 = poly1 + poly2;
    ASSERT_EQ(poly2.GetDimension(),5);
    EXPECT_EQ(poly2[0], 5);
    EXPECT_EQ(poly2[1], 4);
    EXPECT_EQ(poly2[2], 4);
    EXPECT_EQ(poly2[3], 4);
    EXPECT_EQ(poly2[4], 2);
    poly2 = Polynomial(poly1);
    ASSERT_EQ(poly2.GetDimension(),3);
    EXPECT_EQ(poly2[0], 1);
    EXPECT_EQ(poly2[1], 2);
    EXPECT_EQ(poly2[2], 1);
}

TEST(Polynomial, Multiply) {
    Polynomial<int> poly1 = {1, 2, 5};
    Polynomial<int> poly2 = poly1 * 2;
    EXPECT_EQ(poly2[0], 10);
    EXPECT_EQ(poly2[1], 4);
    EXPECT_EQ(poly2[2], 2);

    poly2 = poly1 * poly2;
    EXPECT_EQ(poly2[0], 50);
    EXPECT_EQ(poly2[1], 40);
    EXPECT_EQ(poly2[2], 28);
    EXPECT_EQ(poly2[3], 8);
    EXPECT_EQ(poly2[4], 2);
}
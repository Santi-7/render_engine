/* ---------------------------------------------------------------------------
 ** containerTests.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <point.hpp>
#include <matrix.hpp>


namespace PointTests
{

    /**
     * Test simple addition rules
     */
    TEST(PointAddition, General)
    {
        Point a(1.6, 2.5, 3.5);
        Point b(0.4, 2.5, 4.5);
        Point aPlusB = a + b;
        Point bPlusA = b + a;
        Point expected(2.0, 5.0, 8.0);

        EXPECT_TRUE(expected == aPlusB);
        EXPECT_TRUE(aPlusB == bPlusA);
        EXPECT_FALSE(a == b);
    }

}

namespace MatrixTests
{
    Matrix aMatrix(1, 2, 3, 4,
                   5, 6, 7, 8,
                   9, 10, 11, 12,
                   13, 14, 15, 16);

    Matrix anotherMatrix(0, 1, 0, 1,
                         2, 5, 1, 0,
                         5, 6, 7, 1,
                         5, 1, 1, 6);

    Matrix identity(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);

    Matrix expected(90, 100, 110, 120,
                    202, 228, 254, 280,
                    314, 356, 398, 440,
                    426, 484, 542, 600);

    /**
     * Multiplying a matrix by the identity results in the same matrix
     * no matter on which side the multiplication occurs
     */
    TEST(MatrixMultiplication, Identity) {

        Matrix leftProduct = aMatrix * identity;
        Matrix rightProduct = identity * aMatrix;

        EXPECT_EQ(leftProduct, aMatrix);
        EXPECT_EQ(rightProduct, aMatrix);
        EXPECT_NE(leftProduct, identity);
        EXPECT_NE(rightProduct, identity);
    }

    /**
     * Test the multiplication result is correct and that matrix products are not commutative
     */
    TEST(MatrixMultiplication, ExpectedResult)
    {
        EXPECT_EQ(aMatrix * aMatrix, expected);
        EXPECT_NE(aMatrix * anotherMatrix, anotherMatrix * aMatrix);
    }
}
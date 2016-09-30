/* ---------------------------------------------------------------------------
 ** point.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include <containers/point.hpp>

TEST(Addition, General)
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

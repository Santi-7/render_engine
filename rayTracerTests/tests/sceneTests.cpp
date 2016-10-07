/* ---------------------------------------------------------------------------
** sceneTests.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <pinhole.hpp>

TEST(PinholeTest, Basic)
{
    Pinhole phc;
    Point center(0,0,0);
    LightRay lr(phc.PrimaryRay(center, 50, 50));
    Point p = lr.GetPoint(2.0f);
}
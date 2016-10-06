/* ---------------------------------------------------------------------------
** sceneTests.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <point.hpp>
#include <pinhole.hpp>

TEST(PinholeTest, Basic)
{
    Pinhole phc(Point(0,0,0), Image(400, 400));

}

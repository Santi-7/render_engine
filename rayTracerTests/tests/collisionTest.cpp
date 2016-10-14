/* ---------------------------------------------------------------------------
** collisionTest.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <sphere.hpp>

TEST(RayCollideSphere, Basic)
{
    LightRay lightRay(Point(0,0,0), Point(0,0,1));

    // The lightray fully intersects the sphere
    Sphere sphere1(Point(0,0,3), 1.0);
    EXPECT_EQ(sphere1.Intersect(lightRay), 2.0);

    // The lightray is tangent to the sphere
    Sphere sphere2(Point(0, 1, 3), 1.0);
    EXPECT_EQ(sphere2.Intersect(lightRay), 3.0);

    // The lightray doesn't intersect the sphere
    Sphere sphere3(Point(0, 2, 3), 1.0);
    EXPECT_EQ(sphere3.Intersect(lightRay), FLT_MAX);

    // The lightray doesn't intersect the sphere (which is behind the lightRay)
    Sphere sphere4(Point(0, 0, -3), 1.0);
    EXPECT_EQ(sphere4.Intersect(lightRay), FLT_MAX);
}
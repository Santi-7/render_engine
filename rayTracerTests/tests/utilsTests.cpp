/* ---------------------------------------------------------------------------
 ** utilTests.cpp
 ** Some tests to verify the utils package.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <box.hpp>
#include <color.hpp>
#include <gtest/gtest.h>
#include <image.hpp>
#include <matrix.hpp>
#include <poseTransformationMatrix.hpp>
#include <sphere.hpp>
#include <transformationMatrix.hpp>

using namespace std;

///////////////////////////////////
/// Transformation Matrix Tests////
///////////////////////////////////
TEST(TransformationMatrix, General)
{
    TransformationMatrix tMatrix;

    Matrix nMatrix(1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);

    // This doesn't work
    EXPECT_TRUE(tMatrix == nMatrix);
}

////////////////////////////////////////
/// Pose Transformation Matrix Tests////
////////////////////////////////////////
TEST(PoseTransformationMatrix, General)
{
    Point newOrigin(5,1,4);
    Vect newNormal(-2,2,5);
    newNormal = newNormal.Normalise();
    PoseTransformationMatrix localToGlobal =
            PoseTransformationMatrix::GetPoseTransformation(newOrigin, newNormal);
    EXPECT_EQ(localToGlobal * Point(0, 0, 0), newOrigin);
    EXPECT_EQ(localToGlobal * Vect(0, 0, 1), newNormal);

    PoseTransformationMatrix globalToLocal = localToGlobal.Inverse();
    EXPECT_EQ(globalToLocal * newOrigin, Point(0, 0, 0));
    EXPECT_EQ(globalToLocal * newNormal, Vect(0, 0, 1));
}

///////////////////////////////////
///////PPM Image saving Tests//////
///////////////////////////////////
TEST(CreateMultiColorImage, image)
{
    const unsigned int SIZE = 600;
    Image multi(SIZE, SIZE);

    vector<vector<Color> > drawing
    {
            {Color(255, 255, 255), Color(255, 0, 0)},
            {Color(0, 255, 0), Color(0, 0, 255)}
    };

    for(unsigned long i = 0; i < SIZE/2; ++i)
    {
        for(unsigned long j = 0; j < SIZE/2; ++j)
        {
            multi[i][j] = drawing[0][0];
        }
    }

    for(unsigned long i = 0; i < SIZE/2; ++i)
    {
        for(unsigned long j = SIZE/2; j < SIZE; ++j)
        {
            multi[i][j] = drawing[0][1];
        }
    }

    for(unsigned long i = SIZE/2; i < SIZE; ++i)
    {
        for(unsigned long j = 0; j < SIZE/2; ++j)
        {
            multi[i][j] = drawing[1][0];
        }
    }
    for(unsigned long i = SIZE/2; i < SIZE; ++i)
    {
        for(unsigned long j = SIZE/2; j < SIZE; ++j)
        {
            multi[i][j] = drawing[1][1];
        }
    }
    multi.Save("multicolor.ppm");
}

TEST(LoadTexture, Image)
{
    Image texture(string(PROJECT_DIR) + "/build/cacafuti.ppm");
    texture.Save("loadedTeapot.ppm");
}

////////////////////////////////////////
///////Points inside volume shapes//////
////////////////////////////////////////
TEST(Inside, Sphere)
{
    Sphere s1(Point(0,0,0), 3);
    EXPECT_TRUE(s1.IsInside(Point(0,0,0)));
    EXPECT_FALSE(s1.IsInside(Point(4,0,0)));
}

TEST(Inside, Box)
{
    Box b1(Rectangle(Vect(0,1,0), Point(0,0,0), Point(4,0,4)), 4);
    EXPECT_TRUE(b1.IsInside(Point(2,2,2)));
    EXPECT_FALSE(b1.IsInside(Point(-2,0,0)));
}
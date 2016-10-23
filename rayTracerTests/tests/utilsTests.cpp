/* ---------------------------------------------------------------------------
 ** utilTests.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <color.hpp>
#include <gtest/gtest.h>
#include <image.hpp>
#include <matrix.hpp>
#include <poseTransformationMatrix.hpp>
#include <transformationMatrix.hpp>
#include <mathConstants.hpp>

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

// TODO: Put this in its own file since it's duplicated from poseTransformationMatrix.cpp
static float GetRandomAngle(bool getQuarterOfAnAngle)
{
    static random_device randDev;
    static mt19937 mt(randDev());
    static uniform_real_distribution<float> fullDistribution(0, 2 * PI);
    static uniform_real_distribution<float> quarterDistribution(0, PI/2);
    if(getQuarterOfAnAngle) return quarterDistribution(mt);
    else return fullDistribution(mt);
}

TEST(CorrectRandomness, MinMaxAvg)
{
    double quarters = 0;
    double fulls = 0;
    float min = 999999999;
    float max = 0;
    int its = 1000000;
    for (int i = 0; i < its; ++i) {
        float tmp = GetRandomAngle(false);
        if(tmp < min) min = tmp;
        if(tmp > max) max = tmp;
        fulls += tmp;
        tmp = GetRandomAngle(true);
        quarters += tmp;
    }
    //TODO: Add expects
}
/* ---------------------------------------------------------------------------
 ** utilTests.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <matrix.hpp>
#include <color.hpp>
#include <transformationMatrix.hpp>
#include <image.hpp>

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

///////////////////////////////////
///////PPM Image saving Tests//////
///////////////////////////////////
TEST(CreateMultiColorImage, image)
{
    const unsigned int SIZE = 600;
    Image white(SIZE, SIZE);

    vector<vector<Color> > drawing
    {
            {Color(255, 255, 255), Color(255, 0, 0)},
            {Color(0, 255, 0), Color(0, 0, 255)}
    };

    for(unsigned long i = 0; i < SIZE/2; ++i)
    {
        for(unsigned long j = 0; j < SIZE/2; ++j)
        {
            white[i][j] = drawing[0][0];
        }
    }

    for(unsigned long i = 0; i < SIZE/2; ++i)
    {
        for(unsigned long j = SIZE/2; j < SIZE; ++j)
        {
            white[i][j] = drawing[0][1];
        }
    }

    for(unsigned long i = SIZE/2; i < SIZE; ++i)
    {
        for(unsigned long j = 0; j < SIZE/2; ++j)
        {
            white[i][j] = drawing[1][0];
        }
    }
    for(unsigned long i = SIZE/2; i < SIZE; ++i)
    {
        for(unsigned long j = SIZE/2; j < SIZE; ++j)
        {
            white[i][j] = drawing[1][1];
        }
    }
    // Linking issues with the function SavePPMImage
    white.Save("multicolor.ppm");
}

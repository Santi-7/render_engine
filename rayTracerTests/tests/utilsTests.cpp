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
#include <ppmImage.hpp>

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
TEST(ImageSaveTest, WhiteImage)
{
    const unsigned int SIZE = 600;
    array<array <Color, SIZE>, SIZE > testImage;

    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            testImage.at(i).at(j).SetR(255);
            testImage.at(i).at(j).SetG(255);
            testImage.at(i).at(j).SetB(255);
        }
    }
    // Linking issues with the function SavePPMImage
    //SavePPMImage(testImage, "test.ppm");
}
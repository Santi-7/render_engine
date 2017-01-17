/** ---------------------------------------------------------------------------
 ** simpleTexture.cpp
 ** Implementation for SimpleTexture class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <materials/simpleTexture.hpp>

SimpleTexture::SimpleTexture(const string& filename, Dimension axis, float pixelSize, Vect shift)
: Material(BLACK, BLACK, 0.0f, BLACK, BLACK), mImage(filename), mPixelSize(pixelSize), mShift(shift), mAxis(axis) {}

Color SimpleTexture::GetDiffuse(const Point &point) const
{
    int x = static_cast<int>((point.GetX() > 0 ? point.GetX() + mShift.GetX(): -point.GetX() + mPixelSize + mShift.GetX()) / mPixelSize);
    int y = static_cast<int>((point.GetY() > 0 ? point.GetY() + mShift.GetY(): -point.GetY() + mPixelSize + mShift.GetY()) / mPixelSize);
    int z = static_cast<int>((point.GetZ() > 0 ? point.GetZ() + mShift.GetZ(): -point.GetZ() + mPixelSize + mShift.GetZ()) / mPixelSize);
    int i, j;
    switch (mAxis)
    {
    case X:
        i = y % mImage.GetHeight();
        j = z % mImage.GetWidth();
        break;
    case Y:
        i = z % mImage.GetHeight();
        j = x % mImage.GetWidth();
        break;
    case Z:
        i = y % mImage.GetHeight();
        j = x % mImage.GetWidth();
        break;
    default:
        throw invalid_argument("Not a valid dimension\n");
    }
    return mImage[i][j];
}
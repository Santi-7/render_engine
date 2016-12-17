/* ---------------------------------------------------------------------------
** checkerBoard.cpp
** Implementation for CheckerBoard class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <checkerBoard.hpp>

CheckerBoard::CheckerBoard(const float squareSize, Color color1, Color color2)
: Material(color1, BLACK, 0.0f, BLACK, BLACK),
  mColor1(color1), mColor2(color2), mSquareSize(squareSize)
{}

CheckerBoard::CheckerBoard(const float squareSize, Color color1, Color color2, Color specular)
: Material(color1, specular, 0.0f, BLACK, BLACK),
  mColor1(color1), mColor2(color2), mSquareSize(squareSize)
{}

Color CheckerBoard::GetDiffuse(const Point &point) const
{
    int x = static_cast<int>((point.GetX() > 0 ? point.GetX() : -point.GetX() + mSquareSize) / mSquareSize);
    int y = static_cast<int>((point.GetY() > 0 ? point.GetY() : -point.GetY() + mSquareSize) / mSquareSize);
    int z = static_cast<int>((point.GetZ() > 0 ? point.GetZ() : -point.GetZ() + mSquareSize) / mSquareSize);

    if (!(x % 2) ^ (y % 2) ^ !(z % 2))
        return mColor1;
    else
        return mColor2;
}
/* ---------------------------------------------------------------------------
 ** color.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <color.hpp>

Color::Color()
{
    mR = 0;
    mG = 0;
    mB = 0;
}

Color::Color(const byte r, const byte g, const byte b)
{
    mR = r;
    mG = g;
    mB = b;
}

byte Color::GetR() const
{
    return mR;
}

byte Color::GetG() const
{
    return mG;
}

byte Color::GetB() const
{
    return mB;
}

void Color::SetR(const byte red)
{
    mR = red;
}

void Color::SetG(const byte green)
{
    mG = green;
}

void Color::SetB(const byte blue)
{
    mB = blue;
}
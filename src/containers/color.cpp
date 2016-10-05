/* ---------------------------------------------------------------------------
 ** color.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "color.hpp"

Color::Color(byte r, byte g, byte b)
{
    mR = r;
    mG = g;
    mB = b;
}

Color::Color()
{
    mR = 0;
    mG = 0;
    mB = 0;
}

void Color::SetR(byte red)
{
    mR = red;
}

void Color::SetG(byte green)
{
    mG = green;
}
void Color::SetB(byte blue)
{
    mB = blue;
}

byte Color::GetR()
{
    return mR;
}

byte Color::GetG()
{
    return mG;
}

byte Color::GetB()
{
    return mB;
}



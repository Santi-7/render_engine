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
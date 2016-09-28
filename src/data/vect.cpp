/* ---------------------------------------------------------------------------
** vect.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "vect.hpp"

// TODO: Add doc.
/* */
static const float H = 0;

Vect::Vect(const float x, const float y, const float z)
{
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

float Vect::GetX()
{
    return this->mX;
}

float Vect::GetY()
{
    return this->mY;
}

float Vect::GetZ()
{
    return this->mZ;
}

Vect Vect::operator+(const Vect& v)
{
    const float x = this->mX + v.mX;
    const float y = this->mY + v.mY;
    const float z = this->mZ + v.mZ;
    return Vect(x, y, z);
}
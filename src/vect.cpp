/* ---------------------------------------------------------------------------
** vect.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "vect.hpp"

Vect::Vect(float x, float y, float z)
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
    float x = this->mX + v.mX;
    float y = this->mY + v.mY;
    float z = this->mZ + v.mZ;
    return Vect(x, y, z);
}
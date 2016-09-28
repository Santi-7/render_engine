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

const float Vect::GetX() const
{
    return this->mX;
}

const float Vect::GetY() const
{
    return this->mY;
}

const float Vect::GetZ() const
{
    return this->mZ;
}

const Vect Vect::operator+(const Vect& v) const
{
    const float x = this->mX + v.mX;
    const float y = this->mY + v.mY;
    const float z = this->mZ + v.mZ;
    return Vect(x, y, z);
}

const Vect Vect::operator-(const Vect& v) const
{
    const float x = this->mX - v.mX;
    const float y = this->mY - v.mY;
    const float z = this->mZ - v.mZ;
    return Vect(x, y, z);
}

const Vect Vect::operator*(const float k) const
{
    const float x = this->mX * k;
    const float y = this->mY * k;
    const float z = this->mZ * k;
    return Vect(x, y, z);
}
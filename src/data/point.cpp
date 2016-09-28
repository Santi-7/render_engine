/* ---------------------------------------------------------------------------
 ** point.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "point.hpp"

// TODO: Add doc.
/* */
static const float H = 1;

Point::Point(const float x, const float y, const float z)
{
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

const float Point::GetX() const
{
    return this->mX;
}

const float Point::GetY() const
{
    return this->mY;
}

const float Point::GetZ() const
{
    return this->mZ;
}

const Point Point::operator+(const Point& p) const
{
    const float x = this->mX + p.mX;
    const float y = this->mY + p.mY;
    const float z = this->mZ + p.mZ;
    return Point(x, y, z);
}

const Vect Point::operator-(const Point& p) const
{
    const float x = this->mX - p.mX;
    const float y = this->mY - p.mY;
    const float z = this->mZ - p.mZ;
    return Vect(x, y, z);
}

const Point Point::operator+(const Vect& v) const
{
    const float x = this->mX + v.GetX();
    const float y = this->mY + v.GetY();
    const float z = this->mZ + v.GetZ();
    return Point(x, y, z);
}
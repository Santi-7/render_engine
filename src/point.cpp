/* ---------------------------------------------------------------------------
 ** point.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "point.hpp"

Point::Point(float x, float y, float z)
{
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

float Point::GetX()
{
    return this->mX;
}

float Point::GetY()
{
    return this->mY;
}

float Point::GetZ()
{
    return this->mZ;
}

Point Point::operator+(const Point& p)
{
    float x = this->mX + p.mX;
    float y = this->mY + p.mY;
    float z = this->mZ + p.mZ;
    return Point(x, y, z);
}

Vect Point::operator-(const Point& p)
{
    float x = this->mX - p.mX;
    float y = this->mY - p.mY;
    float z = this->mZ - p.mZ;
    return Vect(x, y, z);
}
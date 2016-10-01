/* ---------------------------------------------------------------------------
** vect.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cmath>
#include <vect.hpp>

const float Vect::H = 0;

Vect::Vect(const float x, const float y, const float z)
{
    mX = x;
    mY = y;
    mZ = z;
}

float Vect::GetX() const
{
    return mX;
}

float Vect::GetY() const
{
    return mY;
}

float Vect::GetZ() const
{
    return mZ;
}

float Vect::Abs() const
{
    return (float) sqrt(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2));
}

Vect Vect::operator+(const Vect& v) const
{
    float x = mX + v.mX;
    float y = mY + v.mY;
    float z = mZ + v.mZ;
    return Vect(x, y, z);
}

Vect Vect::operator-(const Vect& v) const
{
    float x = mX - v.mX;
    float y = mY - v.mY;
    float z = mZ - v.mZ;
    return Vect(x, y, z);
}

Vect Vect::operator*(const float k) const
{
    float x = mX * k;
    float y = mY * k;
    float z = mZ * k;
    return Vect(x, y, z);
}

Vect Vect::DotProduct(const Vect& v) const
{
    float x = mX * v.mX;
    float y = mY * v.mY;
    float z = mZ * v.mZ;
    return Vect(x, y, z);
}

Vect Vect::CrossProduct(const Vect& v) const
{
    float x = mY * v.mZ - mZ * v.mY;
    float y = mX * v.mZ - mZ * v.mX;
    float z = mX * v.mY - mY * v.mX;
    return Vect(x, -y, z);
}

std::ostream& operator<< (std::ostream &out, const Vect &v)
{
    out << "Vector(" << v.mX << ", " << v.mY << ", " << v.mZ << ")";
    return out;
}
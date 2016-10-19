/* ---------------------------------------------------------------------------
** vect.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <math.h>
#include <vect.hpp>

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
    return sqrt(mX*mX + mY*mY + mZ*mZ);
}

Vect Vect::Normalise() const
{
    return *this / this->Abs();
}

Vect Vect::operator*(const float k) const
{
    float x = mX * k;
    float y = mY * k;
    float z = mZ * k;
    return Vect(x, y, z);
}

Vect Vect::operator/(const float k) const
{
    float x = mX / k;
    float y = mY / k;
    float z = mZ / k;
    return Vect(x, y, z);
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

float Vect::DotProduct(const Vect& v) const
{
    return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

Vect Vect::CrossProduct(const Vect& v) const
{
    float x = mY * v.mZ - mZ * v.mY;
    float y = mX * v.mZ - mZ * v.mX;
    float z = mX * v.mY - mY * v.mX;
    return Vect(x, -y, z);
}

bool Vect::operator==(const Vect &v) const
{
    return mX == v.mX & mY == v.mY & mZ == v.mZ;
}

bool Vect::operator!=(const Vect &v) const
{
    return !(*this == v);
}

std::ostream& operator<<(std::ostream &out, const Vect &v)
{
    out << "Vector(" << v.mX << ", " << v.mY << ", " << v.mZ << ")";
    return out;
}
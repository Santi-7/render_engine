/* ---------------------------------------------------------------------------
 ** point.cpp
 ** Implementation for Point class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <cmath>
#include <point.hpp>

Point::Point()
{}

Point::Point(const float x, const float y, const float z)
{
    mX = x;
    mY = y;
    mZ = z;
}

float Point::Distance(const Point &to) const
{
    return (*this - to).Abs();
}

Dimension Point::LongestDimension(const Point &to) const
{
    Dimension longestDimension = X;
    float maxDistance = std::abs(mX - to.mX);
    // Check if dimension Y is longer.
    if (std::abs(mY - to.mY) > maxDistance)
    {
        longestDimension = Y;
        maxDistance = std::abs(mY - to.mY);
    }
    // Check if dimension Z is longer.
    if (std::abs(mZ - to.mZ) > maxDistance)
    {
        longestDimension = Z;
    }
    return longestDimension;
}

float Point::GetX() const
{
    return mX;
}

float Point::GetY() const
{
    return mY;
}

float Point::GetZ() const
{
    return mZ;
}

void Point::SetX(const float x)
{
    mX = x;
}

void Point::SetY(const float y)
{
    mY = y;
}

void Point::SetZ(const float z)
{
    mZ = z;
}

void Point::SetDimension(const Dimension &dimension, const float value)
{
    mContainer[dimension] = value;
}

Point Point::operator+(const Point& p) const
{
    float x = mX + p.mX;
    float y = mY + p.mY;
    float z = mZ + p.mZ;
    return Point(x, y, z);
}

Vect Point::operator-(const Point& p) const
{
    float x = mX - p.mX;
    float y = mY - p.mY;
    float z = mZ - p.mZ;
    return Vect(x, y, z);
}

float Point::operator*(const Point& p) const
{
    return mX * p.mX + mY * p.mY + mZ * p.mZ;
}

Point Point::operator+(const Vect& v) const
{
    float x = mX + v.GetX();
    float y = mY + v.GetY();
    float z = mZ + v.GetZ();
    return Point(x, y, z);
}

void Point::operator+=(const Vect& v)
{
    mX += v.GetX();
    mY += v.GetY();
    mZ += v.GetZ();
}

Point Point::operator-(const Vect& v) const
{
    float x = mX - v.GetX();
    float y = mY - v.GetY();
    float z = mZ - v.GetZ();
    return Point(x, y, z);
}

void Point::operator-=(const Vect& v)
{
    mX -= v.GetX();
    mY -= v.GetY();
    mZ -= v.GetZ();
}

bool Point::operator==(const Point& p) const
{
    return (std::abs(mX - p.GetX()) <= TH) &
           (std::abs(mY - p.GetY()) <= TH) &
           (std::abs(mZ - p.GetZ()) <= TH);
}

bool Point::operator!=(const Point& p) const
{
    return ! (*this == p);
}

bool Point::operator<=(const Point &p) const
{
    return (mX - p.GetX() <= TH) &
           (mY - p.GetY() <= TH) &
           (mZ - p.GetZ() <= TH);
}

bool Point::operator>=(const Point &p) const
{
    return (p.GetX() - mX <= TH) &
           (p.GetY() - mY <= TH) &
           (p.GetZ() - mZ <= TH);
}

std::ostream& operator<<(std::ostream &out, const Point &p)
{
    out << "Point(" << p.mX << ", " << p.mY << ", " << p.mZ << ")";
    return out;
}

float Point::operator[](const Dimension d) const
{
    return mContainer[d];
}

#include "point.hpp"

Point::Point(double x, double y, double z)
{
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

double Point::GetX()
{
    return this->mX;
}

double Point::GetY()
{
    return this->mY;
}

double Point::GetZ()
{
    return this->mZ;
}

Point Point::operator+(const Point& p)
{
    double x = this->mX + p.mX;
    double y = this->mY + p.mY;
    double z = this->mZ + p.mZ;
    return Point(x, y, z);
}
/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begue, NIA: 683482
** -------------------------------------------------------------------------*/

#include "vect.hpp"

Vect::Vect(double x, double y, double z)
{
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

double Vect::GetX()
{
    return this->mX;
}

double Vect::GetY()
{
    return this->mY;
}

double Vect::GetZ()
{
    return this->mZ;
}

Vect Vect::operator+(const Vect& p)
{
    double x = this->mX + p.mX;
    double y = this->mY + p.mY;
    double z = this->mZ + p.mZ;
    return Vect(x, y, z);
}
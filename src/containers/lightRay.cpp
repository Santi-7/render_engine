/* ---------------------------------------------------------------------------
 ** lightRay.cpp
 ** Implementation for LightRay class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <lightRay.hpp>

LightRay::LightRay(const Point &source, const Point &destination)
: mSource(source), mDirection((destination - source).Normalise())
{}

LightRay::LightRay(const Point &source, const Vect &direction)
: mSource(source), mDirection(direction.Normalise())
{}

Point LightRay::GetPoint(const float t) const
{
    return mSource + mDirection * t;
}

Point LightRay::GetSource() const
{
    return mSource;
}

Vect LightRay::GetDirection() const
{
    return mDirection;
}
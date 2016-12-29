/* ---------------------------------------------------------------------------
** coloredLightRay.cpp
** Implementation for ColoredLightRay class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <coloredLightRay.hpp>

ColoredLightRay::ColoredLightRay() {}

ColoredLightRay::ColoredLightRay(const Point &source, const Vect &direction, const Color &color)
: LightRay(source, direction), mColor(color)
{}

Color ColoredLightRay::GetColor() const
{
    return mColor;
}
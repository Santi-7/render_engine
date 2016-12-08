/* ---------------------------------------------------------------------------
** pointLight.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pointLight.hpp>

PointLight::PointLight()
: LightSource(), mPosition(Point(0,0,0))
{}

PointLight::PointLight(const Point &position)
: LightSource(), mPosition(position)
{}

PointLight::PointLight(const Point &position, const float power, const Color &baseColor)
: LightSource(power, baseColor), mPosition(position)
{}

Color PointLight::GetColor(const Point &point) const
{
    // Distance from the given point to the source light.
    float distance = point.Distance(mPosition);
    // Radiance decreases proportionally with the square of the distance.
    return mBaseColor * (mPower / (distance * distance));
}

vector<Point> PointLight::GetLights() const
{
    return vector<Point>{mPosition};
}
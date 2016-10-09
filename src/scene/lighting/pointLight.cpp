/* ---------------------------------------------------------------------------
** pointLight.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pointLight.hpp>

PointLight::PointLight() : LightSource(), mPosition(Point(0,0,0)) {}
PointLight::PointLight(Point position) : LightSource(), mPosition(position) {}
PointLight::PointLight(Point position, float radiance, Color& baseColor) : LightSource(radiance, baseColor), mPosition(position) {}

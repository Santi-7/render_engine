/* ---------------------------------------------------------------------------
** pointLight.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_POINT_LIGHT_HPP
#define RAY_TRACER_POINT_LIGHT_HPP

#include <lightSource.hpp>
#include <point.hpp>

class PointLight : public LightSource {

public:
    PointLight();
    PointLight(Point position);
    PointLight(Point position, float radiance, Color& baseColor);
private:
    Point mPosition;
};

#endif // RAY_TRACER_POINT_LIGHT_HPP
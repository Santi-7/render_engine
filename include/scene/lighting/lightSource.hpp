/* ---------------------------------------------------------------------------
** lightSource.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_LIGHT_SOURCE_HPP
#define RAY_TRACER_LIGHT_SOURCE_HPP

#include <color.hpp>

class LightSource {

protected:
    LightSource() : mRadiance(1.0), mBaseColor(WHITE) {}
    LightSource(float radiance, Color& baseColor) : mRadiance(radiance), mBaseColor(baseColor) {}

    float mRadiance;
    Color mBaseColor;
};

#endif // RAY_TRACER_LIGHT_SOURCE_HPP
/** ---------------------------------------------------------------------------
 ** lightSource.hpp
 ** Defines common values contained within Light Sources.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_LIGHT_SOURCE_HPP
#define RAY_TRACER_LIGHT_SOURCE_HPP

#include <color.hpp>
#include <lightRay.hpp>
#include <memory>
#include <point.hpp>
#include <vector>

class LightSource
{

public:

    /**
     * @param point Point at which the light intensity will be calculated.
     * @return Color with the intensity of this light at point (the farther the point the smaller the intensity).
     */
    virtual Color GetColor(const Point &point) const = 0;

    /**
     * @return List of the lights contained within this lightSource (in case a multi-point lightSource is created).
     */
    virtual vector<Point> GetLights() const = 0;

protected:

    /** This lightSource's power. */
    float mPower;

    /** This light's color. */
    Color mBaseColor;

    /**
     * @return New white lightSource with power 2.0f.
     */
    LightSource()
    : mPower(2.0f), mBaseColor(WHITE)
    {}

    /**
     * @param power The new light's power.
     * @param baseColor The new light's Color.
     * @return New LightSource with the given power and color.
     */
    LightSource(const float power, const Color &baseColor)
    : mPower(power), mBaseColor(baseColor)
    {}
};

#endif // RAY_TRACER_LIGHT_SOURCE_HPP
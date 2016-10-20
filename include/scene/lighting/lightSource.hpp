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
#include <lightRay.hpp>
#include <memory>
#include <point.hpp>
#include <vector>

class LightSource
{

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @return .
     */
    virtual Color GetColor(const Point &point) const = 0;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    virtual vector<Point> GetLights() const = 0;

protected:

    // TODO: Add doc.
    /* . */
    float mPower;

    // TODO: Add doc.
    /* . */
    Color mBaseColor;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    LightSource()
    : mPower(500.0), mBaseColor(WHITE)
    {}

    // TODO: Add doc.
    /**
     * .
     *
     * @param power .
     * @param baseColor .
     * @return
     */
    LightSource(const float power, const Color &baseColor)
    : mPower(power), mBaseColor(baseColor)
    {}
};

#endif // RAY_TRACER_LIGHT_SOURCE_HPP
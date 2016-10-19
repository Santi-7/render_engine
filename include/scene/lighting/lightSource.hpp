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
     * @return .
     */
    virtual vector<Point> GetLights() const = 0;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Color GetBaseColor() const
    {
        return mBaseColor;
    }

protected:

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
    : mBaseColor(WHITE)
    {}

    // TODO: Add doc.
    /**
     * .
     *
     * @param baseColor .
     * @return
     */
    LightSource(const Color &baseColor)
    : mBaseColor(baseColor)
    {}
};

#endif // RAY_TRACER_LIGHT_SOURCE_HPP
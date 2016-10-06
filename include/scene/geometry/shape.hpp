/* ---------------------------------------------------------------------------
** shape.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SHAPE_HPP
#define RAY_TRACER_SHAPE_HPP

#include <lightRay.hpp>

class Shape {

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @return .
     */
    virtual Point Intersect(const LightRay &lightRay) const = 0;
};

#endif // RAY_TRACER_SHAPE_HPP
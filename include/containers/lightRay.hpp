/* ---------------------------------------------------------------------------
 ** lightRay.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_LIGHT_RAY_HPP
#define RAY_TRACER_LIGHT_RAY_HPP

#include <point.hpp>

class LightRay {

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param source .
     * @param destination .
     * @return .
     */
    LightRay(const Point &source, const Point &destination);

    // TODO: Add doc.
    /**
     * .
     *
     * @param t .
     * @return .
     */
    Point GetPoint(const float t) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Point GetSource() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Vect GetDirection() const;

private:

    // TODO: Add doc.
    /* . */
    Point mSource;

    // TODO: Add doc.
    /* . */
    Vect mDirection;
};

#endif // RAY_TRACER_LIGHT_RAY_HPP
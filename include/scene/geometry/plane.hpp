/* ---------------------------------------------------------------------------
** plane.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <shape.hpp>

class Plane : public Shape {

public:

    // TODO: Add doc.
    /**
     * Constructs a Plane.
     *
     * @param point .
     * @param normal .
     * @return .
     */
    Plane(const Point &point, const Vect &normal);

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @return .
     */
    float Intersect(const LightRay &lightRay) const;

private:

    // TODO: Add doc.
    /* . */
    Point mPoint;

    // TODO: Add doc.
    /* . */
    Vect mNormal;
};

#endif // RAY_TRACER_SPHERE_HPP
/* ---------------------------------------------------------------------------
** sphere.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <shape.hpp>

class Sphere : public Shape {

public:

    // TODO: Add doc.
    /**
     * Constructs a Sphere.
     *
     * @param center .
     * @param radius .
     * @return .
     */
    Sphere(const Point &center, const float radius);

    /**
     * .
     *
     * @param p .
     * @param v .
     * @return .
     */
    Point intersect(const Point &p, const Vect &v) const;

private:

    // TODO: Add doc.
    /* . */
    static const float threshold;

    // TODO: Add doc.
    /* . */
    Point mCenter;

    // TODO: Add doc.
    /* . */
    float mRadius;
};

#endif // RAY_TRACER_SPHERE_HPP
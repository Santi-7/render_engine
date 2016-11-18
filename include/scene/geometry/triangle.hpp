/* ---------------------------------------------------------------------------
** triangle.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_TRIANGLE_HPP
#define RAY_TRACER_TRIANGLE_HPP

#include <shape.hpp>

class Triangle : public Shape
{

public:

    // TODO: Add doc.
    /**
     * Constructs a Triangle.
     *
     * @param a .
     * @param b .
     * @param c .
     * @return .
     */
    Triangle(const Point &a, const Point &b, const Point &c);

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @return .
     */
    float Intersect(const LightRay &lightRay) const;

    // TODO: Add doc.
    /**
     * .
     * @param lightRay .
     * @param minT .
     * @param nearestShape .
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param seenFrom .
     * @return .
     */
    Vect GetVisibleNormal(const Point &point,
                          const LightRay &seenFrom) const;

protected:

    // TODO: Add doc.
    /* . */
    Point mA, mB, mC;

    /* Cached values. */

    // TODO: Add doc.
    /* . */
    Vect v0, v1;
    float d00, d01, d11, denominator;
    Plane plane;
};

#endif // RAY_TRACER_TRIANGLE_HPP

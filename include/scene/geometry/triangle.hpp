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

class Triangle : public Shape {

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

private:

    // TODO: Add doc.
    /* . */
    Point mA, mB, mC;
};

#endif // RAY_TRACER_TRIANGLE_HPP
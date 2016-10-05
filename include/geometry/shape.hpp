/* ---------------------------------------------------------------------------
** shape.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SHAPE_HPP
#define RAY_TRACER_SHAPE_HPP

class Shape {

public:

    /**
     * .
     *
     * @param p .
     * @param v .
     * @return .
     */
    Point intersect(const Point p, const Vector v);
};

#endif // RAY_TRACER_SHAPE_HPP
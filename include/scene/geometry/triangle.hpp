/** ---------------------------------------------------------------------------
 ** triangle.hpp
 ** Defines a triangle. A triangle is a section of a plane defined within 3 points.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_TRIANGLE_HPP
#define RAY_TRACER_TRIANGLE_HPP

#include <plane.hpp>

class Triangle : public Plane
{

public:

    /**
     * @param a Point a for the new Triangle.
     * @param b Point b for the new Triangle.
     * @param c Point c for the new Triangle.
     * @return New Triangle with points a, b and c.
     */
    Triangle(const Point &a, const Point &b, const Point &c);

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to this Triangle. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay The LightRay we are checking for intersections.
     * @param minT Distance from the lightRay's origin to nearestShape. Updated to this this Triangle's distance from
     *  the lightRay's origin if that is smaller than minT.
     * @param nearestShape Shape that is at distance t from the lightRay's origin. Updated to thisShape if this Triangle
     *  is closer from the lightRay's origin than minT.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const;

    /**
     * @return This triangles barycenter.
     */
    Point GetCenter() const;

//protected:

    /** The three points that define this triangle . */
    Point mA, mB, mC;

    /* Cached values. */

    /** Barycentric usefulous values . */ // TODO: Explain this better :P
    Vect v0, v1;
    float d00, d01, d11, denominator;
};

#endif // RAY_TRACER_TRIANGLE_HPP
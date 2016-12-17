/* ---------------------------------------------------------------------------
** rectangle.hpp
** Finite 2D plane in a 3D space.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_FINITEPLANE_HPP
#define RAY_TRACER_FINITEPLANE_HPP

#include <plane.hpp>

class Rectangle : public Plane
{

public:

    /**
     * @param normal Normal to the plane in which this Rectangle lies.
     * @param cornerA Corner of the new Rectangle.
     * @param cornerB Corner of the new Rectangle.
     * @return New Rectangle with the given normal and corners. Both corners will be considered diagonally
     * opposite as in they are not connected by any of the Rectangle's edges.
     */
    Rectangle(const Vect &normal, const Point &cornerA, const Point &cornerB);

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to this Rectangle. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay The LightRay we are checking for intersections.
     * @param minT Distance from the lightRay's origin to nearestShape. Updated to this this Rectangle's distance from
     *  the lightRay's origin if that is smaller than minT.
     * @param nearestShape Shape that is at distance t from the lightRay's origin. Updated to thisShape if this Rectangle
     *  is closer from the lightRay's origin than minT.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                   shared_ptr<Shape> thisShape) const;

    /**
     * @return The four corner points of this rectangle.
     */
    tuple<Point, Point, Point, Point> GetLimits() const;

private:

    /** Two diagonally opposite corners of this rectangle. */
    Point mCornerA, mCornerB;

    /** Minimum and maximum values for any coordinate in this rectangle. A combination of mCornerA and mCornerB.*/
    Point mMinimums, mMaximums;
};

#endif // RAY_TRACER_FINITEPLANE_HPP

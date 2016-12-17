/** ---------------------------------------------------------------------------
 ** plane.hpp
 ** Infinite 2D plane in a 3D space.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_PLANE_HPP
#define RAY_TRACER_PLANE_HPP

#include <shape.hpp>

class Plane : public Shape
{

public:

    /**
     * @param point Any point of the plane.
     * @param normal Normal to the plane at any point.
     * @return New Plane with the given point and normal.
     */
    Plane(const Point &point, const Vect &normal);

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to this Plane. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX. Since planes are infinite this
     * can only happen if the lightRay is parallel or has a direction opposite to the plane.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay The LightRay we are checking for intersections.
     * @param minT Distance from the lightRay's origin to nearestShape. Updated to this this Plane's distance from
     *  the lightRay's origin if that is smaller than minT.
     * @param nearestShape Shape that is at distance t from the lightRay's origin. Updated to thisShape if this Plane
     *  is closer from the lightRay's origin than minT.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                   shared_ptr<Shape> thisShape) const;

    /**
     * @return This Plane's normal.
     */
    Vect GetNormal() const;

    /**
     * @param point Point of this plane which normal will be returned.
     * @return This Plane's normal at point. Usually the point won't matter but it could be modified.
     */
    virtual Vect GetNormal(const Point &point) const;

protected:

    /** A point of this plane. */
    Point mPoint;

    /** The vector normal to this plane. */
    Vect mNormal;
};

#endif // RAY_TRACER_PLANE_HPP
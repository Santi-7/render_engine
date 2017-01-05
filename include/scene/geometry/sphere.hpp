/** ---------------------------------------------------------------------------
 ** sphere.hpp
 ** Sphere Shape in the 3D space.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <shape.hpp>

class Sphere : public Shape
{

public:

    /**
     * @param center Center Point of the new Sphere.
     * @param radius Radius of the new Sphere.
     * @return New Sphere with the given center and radius.
     */
    Sphere(const Point &center, const float radius);

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to this Sphere. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay The LightRay we are checking for intersections.
     * @param minT Distance from the lightRay's origin to nearestShape. Updated to this this Sphere's distance from
     *  the lightRay's origin if that is smaller than minT.
     * @param nearestShape Shape that is at distance t from the lightRay's origin. Updated to thisShape if this Sphere
     *  is closer from the lightRay's origin than minT.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                   shared_ptr<Shape> thisShape) const;

    /**
     * @param point Point at which the normal will be calculated.
     * @return Vector normal to this Sphere at point.
     */
    virtual Vect GetNormal(const Point &point) const;

    /**
     * @param radius Radius of the sphere.
     * @return The volume of a sphere with radius [radius].
     */
    static float Volume(const float radius);

private:

    /** Center point of this Sphere. */
    Point mCenter;

    /** Radius of this Sphere. */
    float mRadius;

    /* Cached values. */

    /** Square of this Sphere's radius. */
    float mRadius2;
};

#endif // RAY_TRACER_SPHERE_HPP
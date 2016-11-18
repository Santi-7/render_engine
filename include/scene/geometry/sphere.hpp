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

class Sphere : public Shape
{

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
     * @param t .
     * @param nearestShape .
     */
    void Intersect(const LightRay &lightRay, float &t, shared_ptr<Shape> nearestShape) const;

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

private:

    // TODO: Add doc.
    /* . */
    Point mCenter;

    // TODO: Add doc.
    /* . */
    float mRadius;

    /* Cached values. */

    // TODO: Add doc.
    /* . */
    float mRadius2;
};

#endif // RAY_TRACER_SPHERE_HPP
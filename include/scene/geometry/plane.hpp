/* ---------------------------------------------------------------------------
** plane.hpp
** TODO: Add doc.
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

    // TODO: Add doc.
    /**
     * .
     * @param lightRay .
     * @param minT .
     * @param nearestShape .
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> nearestShape) const;

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

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Vect GetNormal() const;

protected:

    // TODO: Add doc.
    /* . */
    Point mPoint;

    // TODO: Add doc.
    /* . */
    Vect mNormal;
};

#endif // RAY_TRACER_PLANE_HPP
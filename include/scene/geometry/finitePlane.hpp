/* ---------------------------------------------------------------------------
** finitePlane.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_FINITEPLANE_HPP
#define RAY_TRACER_FINITEPLANE_HPP

#include <plane.hpp>

class FinitePlane : public Plane
{

public:

    // TODO: Add doc.
    /**
     * Constructor for a FinitePlane only giving two corners.
     * @param normal
     * @param cornerA
     * @param cornerB
     * @return
     */
    FinitePlane(const Vect &normal, const Point &cornerA, const Point &cornerB);

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
     * @param lightRay
     * @param minT
     * @param nearestShape
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    tuple<Point, Point> GetLimits() const;

private:

    // Todo: Add doc.
    /* . */
    Point mCornerA, mCornerB;

    // Todo: Add doc.
    /* . */
    Point mMinimums, mMaximums;
};

#endif //RAY_TRACER_FINITEPLANE_HPP

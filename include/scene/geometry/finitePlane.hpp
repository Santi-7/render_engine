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

class FinitePlane : public Plane {

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
     *
     * @param point .
     * @param seenFrom .
     * @return .
     */
    Vect GetVisibleNormal(const Point &point,
                          const LightRay &seenFrom) const;
private:
    Point mMinimums, mMaximums;
};

#endif //RAY_TRACER_FINITEPLANE_HPP

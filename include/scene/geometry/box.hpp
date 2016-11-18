/* ---------------------------------------------------------------------------
** box.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_BOX_HPP
#define RAY_TRACER_BOX_HPP

#include <finitePlane.hpp>

class Box : public Shape
{

public:

    // TODO: Add doc.
    /**
     * Constructs a Box.
     *
     * @param base .
     * @param depth .
     * @return .
     */
    Box(const FinitePlane &base, const float depth);

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
    Vect GetVisibleNormal(const Point &point, const LightRay &seenFrom) const;

protected:

    // TODO: Add doc.
    /* . */
    array<shared_ptr<FinitePlane>, 6> mFaces; // A box has 6 faces.
};

#endif //RAY_TRACER_BOX_HPP
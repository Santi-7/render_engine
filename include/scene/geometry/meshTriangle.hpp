/* ---------------------------------------------------------------------------
** meshTriangle.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MESHTRIANGLE_HPP
#define RAY_TRACER_MESHTRIANGLE_HPP

#include <plane.hpp>
#include "triangle.hpp"

class MeshTriangle : public Triangle {

public:

    // TODO: Add doc.
    /**
     * Constructs a Triangle.
     *
     * @param a .
     * @param b .
     * @param c .
     * @return .
     */
    MeshTriangle(const Point &a, const Point &b, const Point &c, const Vect &nA, const Vect &nB, const Vect &nC );

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param seenFrom .
     * @return .
     */
    Vect GetVisibleNormal(const Point &point, const LightRay &seenFrom) const;

private:

    // TODO: Add doc.
    /* . */
    Vect mNormalA, mNormalB, mNormalC;

};

#endif // RAY_TRACER_MESHTRIANGLE_HPP
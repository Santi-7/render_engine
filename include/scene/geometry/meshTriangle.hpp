/** ---------------------------------------------------------------------------
 ** meshTriangle.hpp
 ** Extension of a triangle containing vertex normals for the three points.
 ** This way the normal can be interpolated to give the Mesh using this triangles
 ** a curved appearance with a few triangles.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MESHTRIANGLE_HPP
#define RAY_TRACER_MESHTRIANGLE_HPP

#include <triangle.hpp>

class MeshTriangle : public Triangle
{

public:

    /**
     * @param a Point a for the new Triangle.
     * @param b Point b for the new Triangle.
     * @param c Point c for the new Triangle.
     * @param nA Vector normal to a.
     * @param nB Vector normal to b.
     * @param nC Vector normal to c.
     */
    MeshTriangle(const Point &a, const Point &b, const Point &c,
                 const Vect &nA, const Vect &nB, const Vect &nC);

    /**
     * @param point Point of this triangle at which the normal will be interpolated.
     * @return Interpolated normal at point.
     */
    Vect GetNormal(const Point &point) const;

private:

    /** Normals . */
    Vect mNormalA, mNormalB, mNormalC;
};

#endif // RAY_TRACER_MESHTRIANGLE_HPP
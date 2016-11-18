/* ---------------------------------------------------------------------------
** meshTriangle.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <plane.hpp>
#include <meshTriangle.hpp>
#include <cmath>

MeshTriangle::MeshTriangle(const Point &a, const Point &b, const Point &c, const Vect &nA, const Vect &nB, const Vect &nC )
        : Triangle(a, b, c), mNormalA(nA), mNormalB(nB), mNormalC(nC),
          // Cached values.
          v0(b - a),
          v1(c - a),
          d00(v0.DotProduct(v0)),
          d01(v0.DotProduct(v1)),
          d11(v1.DotProduct(v1)),
          denominator(d00 * d11 - d01 * d01),
          plane(mA, v0.CrossProduct(v1).Normalise()) {}

Vect MeshTriangle::GetNormal(const Point &point) const
{

    Vect u = mA - mB;

    Vect v = mC - mB;

    Vect n = point - mB;

    double dU = u.Abs();
    double dV = v.Abs();
    double dN = n.Abs();

    u = u.Normalise();
    n = n.Normalise();

    double cost = n.DotProduct(u);

    if (cost < 0) cost = 0;
    if (cost > 1) cost = 1;

    double t = static_cast<float>(cos(cost));

    double distY = 0, distX = 0;
    distX = dN * static_cast<float>(cos(t));
    distY = dN * static_cast<float>(sin(t));

    double uDist = distX/ dU;
    double vDist = distY/ dV;


    return Vect((float)-((1.0 - (uDist + vDist)) * mNormalA.GetX() + mNormalA.GetY() * uDist + mNormalA.GetZ() * vDist),
                (float)-((1.0 - (uDist + vDist)) * mNormalB.GetX() + mNormalB.GetY() * uDist + mNormalB.GetZ() * vDist),
                (float)-((1.0 - (uDist + vDist)) * mNormalC.GetX() + mNormalC.GetY() * uDist + mNormalC.GetZ() * vDist));
}
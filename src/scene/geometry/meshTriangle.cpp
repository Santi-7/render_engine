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
        : Triangle(a, b, c), mNormalA(nA), mNormalB(nB), mNormalC(nC){}

Vect MeshTriangle::GetVisibleNormal(const Point &point, const LightRay &seenFrom) const
{
    return Triangle::GetVisibleNormal(point, seenFrom);
    /*Vect u = mA - mB;

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
                (float)-((1.0 - (uDist + vDist)) * mNormalC.GetX() + mNormalC.GetY() * uDist + mNormalC.GetZ() * vDist));*/
}


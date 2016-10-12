/* ---------------------------------------------------------------------------
** triangle.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <plane.hpp>
#include <triangle.hpp>
#include <cmath>

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
: Shape(),
  mA(a),
  mB(b),
  mC(c),
  // Cached values.
  v0(b - a),
  v1(c - a),
  d00(v0.DotProduct(v0)),
  d01(v0.DotProduct(v1)),
  d11(v1.DotProduct(v1)),
  denominator(d00 * d11 - d01 * d01),
  plane(mA, v0.CrossProduct(v1).Normalise())
{}

// TODO: Check if t = threshold, this is, the lightray lies inside the plane.
float Triangle::Intersect(const LightRay &lightRay) const
{
    // Intersection of the ray of light with the plane.
    float t = plane.Intersect(lightRay);
    Point intersection = lightRay.GetPoint(t);
    // Based in Christer Ericson's Real-Time Collision Detection.
    /* Get the barycentric coordinates for the intersection
     * point with respect to the triangle. */
    Vect v2 = intersection - mA;
    float d20 = v2.DotProduct(v0);
    float d21 = v2.DotProduct(v1);
    // Barycentric coordinates.
    float alpha = (d11 * d20 - d01 * d21) / denominator;
    float beta = (d00 * d21 - d01 * d20) / denominator;
    // Gamma is not necessary: float gamma = 1.0f - alpha - beta;
    // Check if the intersection point is inside the triangle bounds.
    return alpha >= 0 & beta >= 0 & alpha + beta < 1 ? t : FLT_MAX;
}

Vect Triangle::GetNormal(const Point &point) const
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

    double t = cos(cost);

    double distY = 0, distX = 0;
    distX = dN * cos(t);
    distY = dN * sin(t);

    double uDist = distX/ dU;
    double vDist = distY/ dV;


    return Vect((float)-((1.0 - (uDist + vDist)) * mA.GetNormal().GetX() + mA.GetNormal().GetY() * uDist + mA.GetNormal().GetZ() * vDist),
                (float)-((1.0 - (uDist + vDist)) * mB.GetNormal().GetX() + mB.GetNormal().GetY() * uDist + mB.GetNormal().GetZ() * vDist),
                (float)-((1.0 - (uDist + vDist)) * mC.GetNormal().GetX() + mC.GetNormal().GetY() * uDist + mC.GetNormal().GetZ() * vDist));
}
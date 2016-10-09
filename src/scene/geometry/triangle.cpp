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

Triangle::Triangle(const Point &a, const Point &b, const Point &c)
: Shape(),
  mA(a),
  mB(b),
  mC(c)
{}

// TODO: Check if t = threshold, this is, the lightray lies inside the plane.
float Triangle::Intersect(const LightRay &lightRay) const
{
    // Construct the plane where the triangle lies.
    Vect normal = (mB - mA).CrossProduct(mC - mA).Normalise();
    Plane plane(mA, normal);
    // Intersection of the ray of light with the plane.
    float t = plane.Intersect(lightRay);
    Point intersection = lightRay.GetPoint(t);
    // Based in Christer Ericson's Real-Time Collision Detection.
    /* Get the barycentric coordinates for the intersection
     * point with respect to the triangle. */
    Vect v0 = mB - mA, v1 = mC - mA, v2 = intersection - mA;
    float d00 = v0.DotProduct(v0);
    float d01 = v0.DotProduct(v1);
    float d11 = v1.DotProduct(v1);
    float d20 = v2.DotProduct(v0);
    float d21 = v2.DotProduct(v1);
    float denominator = d00 * d11 - d01 * d01;
    // Barycentric coordinates.
    float alpha = (d11 * d20 - d01 * d21) / denominator;
    float beta = (d00 * d21 - d01 * d20) / denominator;
    // Gamma is not necessary: float gamma = 1.0f - alpha - beta;
    // Check if the intersection point is inside the triangle bounds.
    return alpha >= 0 & beta >= 0 & alpha + beta < 1 ? t : FLT_MAX;
}
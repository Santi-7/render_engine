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
: Plane(a, (b-a).CrossProduct(c-a).Normalise()),
  mA(a),
  mB(b),
  mC(c),
  // Cached values.
  v0(b - a),
  v1(c - a),
  d00(v0.DotProduct(v0)),
  d01(v0.DotProduct(v1)),
  d11(v1.DotProduct(v1)),
  denominator(d00 * d11 - d01 * d01)
{}

// TODO: Check if t = threshold, this is, the lightray lies inside the plane.
float Triangle::Intersect(const LightRay &lightRay) const
{
    // Intersection of the ray of light with the plane.
    float t = Plane::Intersect(lightRay);
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

void Triangle::Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const
{
    float tmpT = Intersect(lightRay);
    if (tmpT < minT)
    {
        minT = tmpT;
        nearestShape = thisShape;
    }
}
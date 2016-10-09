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

float Triangle::Intersect(const LightRay &lightRay) const
{
    // Construct the plane where the triangle lies.
    Vect normal = (mB - mA).CrossProduct(mC - mA).Normalise();
    Plane plane(mA, normal);
    // Intersection of the light of ray with the plane.
    float t = plane.Intersect(lightRay);
    Point intersection = lightRay.GetSource() + lightRay.GetDirection() * t;
    // TODO: Check if t = threshold, this is lightray lies inside the plane.
    // Check if the intersection point is inside the triangle bounds.

}
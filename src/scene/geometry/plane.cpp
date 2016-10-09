/* ---------------------------------------------------------------------------
** plane.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <cmath>
#include <intersections.hpp>
#include <plane.hpp>

Plane::Plane(const Point &point, const Vect &normal)
: Shape(),
  mPoint(point),
  mNormal(normal)
{}

float Plane::Intersect(const LightRay &lightRay) const
{
    float numerator = (lightRay.GetSource() - mPoint).DotProduct(mNormal);
    float denominator = lightRay.GetDirection().DotProduct(mNormal);
    // Ordered by probability of occurrence.
    /* The ray of light intersects with the plane. */
    if (numerator != 0 & denominator != 0)
    {
        float t = numerator / denominator;
        /* Return the t distance if the intersection
         * point is in front of the camera. */
        return GetNearestInFront(t);
    }
    /* The ray of light is parallel to the plane
     * and does not intersect in a finite time. */
    else if (numerator != 0 & numerator == 0)
    {
        return FLT_MAX;
    }
    /* The ray lies entirely in the plane. */
    else // numerator == 0 & numerator == 0.
    {
        // TODO: Ask to Adolfo.
        return threshold;
    }
}
/* ---------------------------------------------------------------------------
** sphere.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cmath>
#include <intersections.hpp>
#include <sphere.hpp>

Sphere::Sphere(const Point &center, const float radius)
: Shape(), mCenter(center), mRadius(radius)
{}

unique_ptr<Point> Sphere::Intersect(const LightRay &lightRay) const
{
    float a = lightRay.GetDirection().DotProduct(lightRay.GetDirection());
    // Shorted to gain efficiency.
    float b = 2 * lightRay.GetDirection().DotProduct(lightRay.GetSource() - mCenter);
    float c = lightRay.GetSource() * lightRay.GetSource() +
              mCenter * mCenter -
              2 * (lightRay.GetSource() * mCenter) -
              mRadius * mRadius;
    float bb_4ac = b*b - 4*a*c;
    // Ordered by probability of occurrence.
    /* The ray of light doesn't intersect with the sphere. */
    if (bb_4ac < 0)
    {
        return nullptr;
    }
    /* The ray of light intersects with the sphere. */
    else if (bb_4ac > 0)
    {
        float t_1 = (float) (-b - sqrt(bb_4ac)) / (2 * a);
        float t_2 = (float) (-b + sqrt(bb_4ac)) / (2 * a);
        return GetIntersection(lightRay, t_1, t_2);
    }
    /* The ray of light is a tangent line of the sphere. */
    else // (b*b - 4*a*c = 0)
    {
        float t = -b / (2 * a);
        return GetIntersection(lightRay, t);
    }
}
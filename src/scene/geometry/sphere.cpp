/* ---------------------------------------------------------------------------
** sphere.cpp
** Implementation for Sphere class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <intersections.hpp>
#include <sphere.hpp>

Sphere::Sphere(const Point &center, const float radius)
: Shape(),
  mCenter(center),
  mRadius(radius),
  // Cached values.
  mRadius2(mRadius * mRadius)
{}

float Sphere::Intersect(const LightRay &lightRay) const
{
    // Shortened to gain efficiency.
    Vect v = lightRay.GetSource() - mCenter;
    float a = lightRay.GetDirection().DotProduct(lightRay.GetDirection());
    float b = 2 * lightRay.GetDirection().DotProduct(v);
    float c = v.DotProduct(v) - mRadius2;
    float bb_4ac = b*b - 4*a*c;
    // Ordered by probability of occurrence.
    /* The ray of light doesn't intersect with the sphere. */
    if (bb_4ac < 0)
    {
        return FLT_MAX;
    }
    /* The ray of light intersects with the sphere. */
    else if (bb_4ac > 0)
    {
        float t_1 = (-b - sqrt(bb_4ac)) / (2 * a);
        float t_2 = (-b + sqrt(bb_4ac)) / (2 * a);
        return GetNearestInFront(t_1, t_2);
    }
    /* The ray of light is a tangent line of the sphere. */
    else // (b*b - 4*a*c = 0)
    {
        float t = -b / (2 * a);
        return GetNearestInFront(t);
    }
}

void Sphere::Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                       shared_ptr<Shape> thisShape) const
{
    float tmpT = Intersect(lightRay);
    if (tmpT < minT)
    {
        minT = tmpT;
        nearestShape = thisShape;
    }
}

bool Sphere::IsInside(const Point &point) const
{
    return point.Distance(mCenter) <= mRadius;
}

Vect Sphere::GetNormal(const Point &point) const
{
    return (mCenter - point) / mRadius;
}

float Sphere::Volume(const float radius)
{
    return (4.0f / 3.0f) * PI * radius * radius * radius;
}
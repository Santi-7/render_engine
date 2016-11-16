/* ---------------------------------------------------------------------------
** finitePlane.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <finitePlane.hpp>
#include <cfloat>

/**
 * Returns a Point which values are the minimums between the values in a and b
 * @param a
 * @param b
 * @return
 */
inline Point GetMinimumValues(const Point &a, const Point &b)
{
    return Point(min(a.GetX(), b.GetX()),
                 min(a.GetY(), b.GetY()),
                 min(a.GetZ(), b.GetZ()));
}

/**
 * Returns a Point which values are the maximum between the values in a and b
 * @param a
 * @param b
 * @return
 */
inline Point GetMaximumValues(const Point &a, const Point &b)
{
    return Point(max(a.GetX(), b.GetX()),
                 max(a.GetY(), b.GetY()),
                 max(a.GetZ(), b.GetZ()));
}

FinitePlane::FinitePlane(const Vect &normal, const Point &cornerA, const Point &cornerB) :
        mMinimums(GetMinimumValues(cornerA, cornerB)),
        mMaximums(GetMaximumValues(cornerA, cornerB)),
        Plane(cornerA, normal) {}


float FinitePlane::Intersect(const LightRay &lightRay) const
{
    float t = Plane::Intersect(lightRay);
    Point intersection = lightRay.GetPoint(t);
    if(intersection >= mMinimums & intersection <= mMaximums)
    {
        return t;
    }
    return FLT_MAX;
}

Vect FinitePlane::GetVisibleNormal(const Point &point, const LightRay &seenFrom) const
{
    return Plane::GetVisibleNormal(point, seenFrom);
}


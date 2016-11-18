/* ---------------------------------------------------------------------------
** finitePlane.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <finitePlane.hpp>

/**
 * Returns a Point which values are the minimums between the values in a and b.
 *
 * @param a .
 * @param b .
 * @return .
 */
inline Point GetMinimumValues(const Point &a, const Point &b)
{
    return Point(min(a.GetX(), b.GetX()),
                 min(a.GetY(), b.GetY()),
                 min(a.GetZ(), b.GetZ()));
}

/**
 * Returns a Point which values are the maximum between the values in a and b.
 *
 * @param a .
 * @param b .
 * @return .
 */
inline Point GetMaximumValues(const Point &a, const Point &b)
{
    return Point(max(a.GetX(), b.GetX()),
                 max(a.GetY(), b.GetY()),
                 max(a.GetZ(), b.GetZ()));
}

FinitePlane::FinitePlane(const Vect &normal, const Point &cornerA, const Point &cornerB)
: Plane(cornerA, normal),
  mCornerA(cornerA),
  mCornerB(cornerB),
  mMinimums(GetMinimumValues(cornerA, cornerB)),
  mMaximums(GetMaximumValues(cornerA, cornerB))
{}

float FinitePlane::Intersect(const LightRay &lightRay) const
{
    float t = Plane::Intersect(lightRay);
    Point intersection = lightRay.GetPoint(t);
    // The ray of light intersects with the finite plane.
    if (intersection >= mMinimums & intersection <= mMaximums)
    {
        return t;
    }
    // The ray of light doesn't intersect with the finite plane.
    else
    {
        return FLT_MAX;
    }
}

tuple<Point, Point> FinitePlane::GetLimits() const
{
    make_tuple(mCornerA, mCornerB);
}
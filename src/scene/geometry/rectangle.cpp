/* ---------------------------------------------------------------------------
** finitePlane.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <rectangle.hpp>

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

Rectangle::Rectangle(const Vect &normal, const Point &cornerA, const Point &cornerB)
: Plane(cornerA, normal),
  mCornerA(cornerA),
  mCornerB(cornerB),
  mMinimums(GetMinimumValues(cornerA, cornerB)),
  mMaximums(GetMaximumValues(cornerA, cornerB))
{}

float Rectangle::Intersect(const LightRay &lightRay) const
{
    float t = Plane::Intersect(lightRay);
    Point intersection = lightRay.GetPoint(t);
    // The ray of light intersects with the rectangle.
    if (intersection >= mMinimums & intersection <= mMaximums)
    {
        return t;
    }
    // The ray of light doesn't intersect with the rectangle.
    else
    {
        return FLT_MAX;
    }
}

void Rectangle::Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const
{
    float tmpT = Intersect(lightRay);
    if(tmpT < minT)
    {
        minT = tmpT;
        nearestShape = thisShape;
    }
}

tuple<Point, Point, Point, Point> Rectangle::GetLimits() const
{
    Vect halfDiagonalAB = (mCornerA - mCornerB) / 2;
    // The center of the rectangle.
    Point center = mCornerB + halfDiagonalAB;
    // In a rectangle, the distance from each vertex to its center is the same.
    Vect halfDiagonalA2B2 = halfDiagonalAB.CrossProduct(mNormal);
    // The other two vertexes of the tectangle.
    Point cornerA2 = center - halfDiagonalA2B2;
    Point cornerB2 = center + halfDiagonalA2B2;
    // Return the 4 vertexes of the rectangle.
    return make_tuple(mCornerA, cornerA2, mCornerB, cornerB2);
}
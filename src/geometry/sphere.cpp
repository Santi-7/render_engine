/* ---------------------------------------------------------------------------
** sphere.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <sphere.hpp>

Sphere::Sphere(const Point &center, const float radius)
: Shape(), mCenter(center), mRadius(radius)
{}

Point Sphere::intersect(const Point &p, const Vect &v) const
{

}
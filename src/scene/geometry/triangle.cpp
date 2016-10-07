/* ---------------------------------------------------------------------------
** triangle.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <triangle.hpp>

Triangle::Triangle(const Point &a, const Point &b, const Point &c)
: Shape(),
  mA(a),
  mB(b),
  mC(c)
{}

float Triangle::intersect(const LightRay &lightRay) const
{

}
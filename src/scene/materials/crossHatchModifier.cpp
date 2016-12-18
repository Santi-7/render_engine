/* ---------------------------------------------------------------------------
** crossHatchModifier.cpp
** Implementation for CrossHatchModifier class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cmath>
#include <crossHatchModifier.hpp>
#include <transformationMatrix.hpp>

using namespace std;

CrossHatchModifier::CrossHatchModifier(float xDist, float yDist, float zDist)
        :mXDist(xDist), mYDist(yDist), mZDist(zDist)
{}

Vect CrossHatchModifier::Modify(const Vect &vect, const Point &point) const
{
    TransformationMatrix tm;
    tm.SetXRotation(abs(sin(point.GetX()) * mXDist));
    tm.SetYRotation(abs(sin(point.GetY()) * mYDist));
    tm.SetZRotation(abs(sin(point.GetZ()) * mZDist));
    return (tm * vect).Normalise();
}
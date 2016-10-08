/* ---------------------------------------------------------------------------
** pinhole.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pinhole.hpp>

Pinhole::Pinhole()
: Camera()
{}

Pinhole::Pinhole(const Vect &up, const Vect &right,
                 const Vect &towards, const Point &focalPoint,
                 const float fieldOfVision, const float viewPlaneDistance,
                 const unsigned int width, const unsigned int height)
: Camera(up, right, towards, focalPoint, fieldOfVision,
         viewPlaneDistance, width, height)
{}

Point Pinhole::GetFirstPixel() const
{
    Point middle = mFocalPoint + mTowards * mViewPlaneDistance;
    Point first = middle - mRight * ((mWidth - 1 ) / 2.0)
                         + mUp * ((mHeight - 1 ) / 2.0);
    return first;
}
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

LightRay Pinhole::PrimaryRay(const Point &origin, const int x, const int y) const
{
    Point pixelCenter ((x / mWidth) * mViewPlaneDistance * pixelSize * mWidth,
                      -(y / mHeight) * mViewPlaneDistance * pixelSize,
                      mViewPlaneDistance);

    return LightRay(origin, origin - pixelCenter);
}
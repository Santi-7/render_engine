/* ---------------------------------------------------------------------------
** pinhole.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pinhole.hpp>

Pinhole::Pinhole()
: Camera(), mUp(Vect(0,1,0)), mRight(Vect(1,0,0)), mTowards(Vect(0,0,1)),
  mFocalPoint(Point(0,0,0)), mFoV(PI / 2), mViewPlaneDistance(1.0),
  mWidth(256), mHeight(256)
{}

Pinhole::Pinhole(const Vect &up, const Vect &right,
                 const Vect &towards, const Point &focalPoint,
                 const float fieldOfVision, const float imagePlaneDistance,
                 const unsigned int width, const unsigned int height)
: Camera(), mUp(up), mRight(right), mTowards(towards), mFocalPoint(focalPoint),
  mFoV(fieldOfVision), mViewPlaneDistance(imagePlaneDistance),
  mWidth(width), mHeight(height)
{}

LightRay Pinhole::PrimaryRay(const int x, const int y) const
{
    // TODO: Get the point for the given pixel
}
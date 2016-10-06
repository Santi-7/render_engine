/* ---------------------------------------------------------------------------
** pinhole.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <math.h>
#include <pinhole.hpp>

// May not be used
float verticalFOV;
float pixelVerticalAngle;
float pixelHorizontalAngle;

Pinhole::Pinhole(Point focalPoint, Image viewPlane)
: Camera(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), focalPoint,
  (float) (M_1_PI / 2), 1.0f), mImage(viewPlane)
{
    pixelVerticalAngle = mFOV / mImage.GetHeight();
    pixelHorizontalAngle = mFOV / mImage.GetWidth();
    verticalFOV = pixelVerticalAngle * mImage.GetHeight();
}

LightRay Pinhole::PrimaryRay(const int x, const int y) const
{
    // TODO: Get the point for the given pixel
}
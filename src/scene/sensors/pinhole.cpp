/* ---------------------------------------------------------------------------
** pinhole.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pinhole.hpp>

float pixelSize;

Pinhole::Pinhole() : Camera()
{
    mUp = Vect(0,1,0);
    mRight = Vect(1,0,0);
    mTowards = Vect(0,0,1);
    mFocalPoint = Point(0,0,0);
    mFoV = PI / 2;
    mViewPlaneDistance = 1.0;
    mWidth = 256;
    mHeight = 256;
    pixelSize = static_cast<float> ((2.0 * tan(mFoV/2.0))/mHeight);
}

Pinhole::Pinhole(const Vect &up, const Vect &right,
                 const Vect &towards, const Point &focalPoint,
                 const float fieldOfVision, const float viewPlaneDistance,
                 const unsigned int width, const unsigned int height)
{
    mUp = up;
    mRight = right;
    mTowards = towards;
    mFocalPoint = focalPoint;
    mFoV = fieldOfVision;
    mViewPlaneDistance = viewPlaneDistance;
    mWidth = width;
    mHeight = height;
}

LightRay Pinhole::PrimaryRay(Point &origin, const int x, const int y) const
{
    Point pixelCenter ((x / mWidth) * mViewPlaneDistance * pixelSize * mWidth,
                      -(y / mHeight) * mViewPlaneDistance * pixelSize,
                      mViewPlaneDistance);

    return LightRay(origin, origin - pixelCenter);
}
/* ---------------------------------------------------------------------------
** camera.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <camera.hpp>
#include <mathConstants.hpp>

Camera::Camera()
: mUp(0,1,0),
  mRight(1,0,0),
  mTowards(0,0,1),
  mFocalPoint(0,0,0),
  mFoV(PI / 3),
  mViewPlaneDistance(1.0),
  mWidth(256),
  mHeight(256)
{
    CalculatePixelSize();
}

Camera::Camera(const Vect &up, const Vect &right,
               const Vect &towards, const Point &focalPoint,
               const float fieldOfVision, const float viewPlaneDistance,
               const unsigned int width, const unsigned int height)
: mUp(up),
  mRight(right),
  mTowards(towards),
  mFocalPoint(focalPoint),
  mFoV(fieldOfVision),
  mViewPlaneDistance(viewPlaneDistance),
  mWidth(width),
  mHeight(height)
{
    CalculatePixelSize();
}

void Camera::CalculatePixelSize()
{
    mPixelSize = static_cast<float> ((2.0 * tan(mFoV / 2.0)) / mHeight);
}

Vect Camera::GetUp() const
{
    return mUp;
}

Vect Camera::GetRight() const
{
    return mRight;
}

Vect Camera::GetTowards() const
{
    return mTowards;
}

Point Camera::GetFocalPoint() const
{
    return mFocalPoint;
}

unsigned int Camera::GetWidth() const
{
    return mWidth;
}

unsigned int Camera::GetHeight() const
{
    return mHeight;
}

float Camera::GetPixelSize() const
{
    return mPixelSize;
}
/* ---------------------------------------------------------------------------
** camera.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <camera.hpp>

Camera::Camera(const Vect &up, const Vect &right,
               const Vect &towards, const Point &focalPoint,
               const float fieldOfVision, const float imagePlaneDistance)
:  mUp(up), mRight(right), mTowards(towards), mFocalPoint(focalPoint),
   mFOV(fieldOfVision), mViewPlaneDistance(imagePlaneDistance)
{}

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
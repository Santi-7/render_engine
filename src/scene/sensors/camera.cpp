/* ---------------------------------------------------------------------------
** camera.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <camera.hpp>

Camera::Camera(Vect up, Vect right, Vect towards, Point focalPoint, float fieldOfVision, float imagePlaneDistance):
        mUp(up), mRight(right), mTowards(towards), mFocalPoint(focalPoint), mFOV(fieldOfVision), mViewPlaneDistance(imagePlaneDistance)
{}

Vect Camera::GetUp()
{
    return mUp;
}

Vect Camera::GetRight()
{
    return mRight;
}

Vect Camera::GetTowards()
{
    return mTowards;
}


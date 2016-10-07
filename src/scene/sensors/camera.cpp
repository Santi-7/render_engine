/* ---------------------------------------------------------------------------
** camera.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <camera.hpp>

Camera::Camera() : mUp(0,0,0), mRight(1,0,0), mTowards(0,0,1), mFocalPoint(0,0,0) {}

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


/* ---------------------------------------------------------------------------
** camera.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <camera.hpp>

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
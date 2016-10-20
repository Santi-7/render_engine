/* ---------------------------------------------------------------------------
** visibleNormal.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <math.h>
#include <visibleNormal.hpp>

Vect VisibleNormal(const Vect &normal, const Vect &seenFrom)
{
    // Take the normal which looks at the visible semi-sphere.
    float cosine = normal.DotProduct(seenFrom);
    if ((cosine > 0) | (cosine == 0 &
                        signbit(normal.GetX()) == signbit(seenFrom.GetX()) &
                        signbit(normal.GetY()) == signbit(seenFrom.GetY()) &
                        signbit(normal.GetZ()) == signbit(seenFrom.GetZ())))
    {
        return normal * -1;
    }
    else
    {
        return normal;
    }
}
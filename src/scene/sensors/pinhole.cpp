/* ---------------------------------------------------------------------------
** pinhole.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pinhole.hpp>
#include <math.h>

Pinhole::Pinhole(Point focalPoint, Image viewPlane) :
        Camera(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), focalPoint, (float)(M_1_PI/2), 1.0f), mImage(viewPlane)
{}

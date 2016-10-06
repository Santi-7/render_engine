/* ---------------------------------------------------------------------------
** camera.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_CAMERA_HPP
#define RAY_TRACER_CAMERA_HPP

#include <vect.hpp>
#include <point.hpp>

class Camera {

public:
    Camera(Vect x, Vect y, Vect z, Point focalPoint, float fieldOfVision, float imagePlaneDistance);

    Vect GetX();

    Vect GetY();

    Vect GetZ();

private:

    Point mFocalPoint;
    Vect mX, mY, mZ;

    float mFOV;
    float mImagePlaneDistance;
};

#endif // RAY_TRACER_CAMERA_HPP
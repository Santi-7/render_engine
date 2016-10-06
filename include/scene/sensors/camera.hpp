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

    Camera();
    Camera(Vect up, Vect right, Vect towards, Point focalPoint, float fieldOfVision, float ViewPlaneDistance);

    Vect GetUp();

    Vect GetRight();

    Vect GetTowards();

protected:

    Point mFocalPoint;
    Vect mUp, mRight, mTowards;

    float mFOV;
    float mViewPlaneDistance;
};

#endif // RAY_TRACER_CAMERA_HPP
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

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Camera();

    // TODO: Add doc.
    /**
     * .
     *
     * @param up .
     * @param right .
     * @param towards .
     * @param focalPoint .
     * @param fieldOfVision .
     * @param viewPlaneDistance .
     * @return .
     */
    Camera(const Vect &up, const Vect &right,
           const Vect &towards, const Point &focalPoint,
           const float fieldOfVision, const float viewPlaneDistance);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Vect GetUp() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Vect GetRight() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Vect GetTowards() const;

protected:

    // TODO: Add doc.
    /* . */
    Point mFocalPoint;

    // TODO: Add doc.
    /* . */
    Vect mUp, mRight, mTowards;

    // TODO: Add doc.
    /* . */
    float mFOV;

    // TODO: Add doc.
    /* . */
    float mViewPlaneDistance;
};

#endif // RAY_TRACER_CAMERA_HPP
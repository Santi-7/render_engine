/* ---------------------------------------------------------------------------
** camera.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_CAMERA_HPP
#define RAY_TRACER_CAMERA_HPP

#include <lightRay.hpp>
#include <vect.hpp>

class Camera {

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param x .
     * @param y .
     * @return .
     */
    virtual LightRay PrimaryRay(const int x, const int y) const = 0;

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
    const float PI = static_cast<float>(3.141592653589793238463);

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

    // TODO: Add doc.
    /* . */
    unsigned int mWidth, mHeight;
};

#endif // RAY_TRACER_CAMERA_HPP
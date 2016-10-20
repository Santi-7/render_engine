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
#include <math.h>
#include <vect.hpp>

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
     * @param width .
     * @param height .
     * @return .
     */
    Camera(const Vect &up, const Vect &right,
           const Vect &towards, const Point &focalPoint,
           const float fieldOfVision, const float viewPlaneDistance,
           const unsigned int width, const unsigned int height);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    virtual Point GetFirstPixel() const = 0;

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

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Point GetFocalPoint() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    unsigned int GetWidth() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    unsigned int GetHeight() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    float GetPixelSize() const;

protected:

    // TODO: Add doc.
    /* . */
    static constexpr float PI = 3.1415926535897932f;

    // TODO: Add doc.
    /* . */
    Vect mUp, mRight, mTowards;

    // TODO: Add doc.
    /* . */
    Point mFocalPoint;

    // TODO: Add doc.
    /* . */
    float mFoV;

    // TODO: Add doc.
    /* . */
    float mViewPlaneDistance;

    // TODO: Add doc.
    /* . */
    unsigned int mWidth, mHeight;

    /* Cached values. */

    // TODO: Add doc.
    /* . */
    float mPixelSize;

private:

    // TODO: Add doc.
    /**
     * .
     */
    void CalculatePixelSize();
};

#endif // RAY_TRACER_CAMERA_HPP
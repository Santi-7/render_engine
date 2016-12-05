/** ---------------------------------------------------------------------------
 ** camera.hpp
 ** Abstract Camera for ray tracing. Must be defined for a scene to produce an image.
 ** The resulting image size is defined in the camera to allow traversing
 ** all the pixels that need tracing.
 ** From this camera we create a pinhole camera but we could extend it to be a
 ** fish eye camera or something else.
 ** //TODO: NOT REALLY! What we can change is not enough to make a fish eye (the image is traversed in scene!!!), this should just be a pinhole camera.
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

    /**
     * @return New Camera with default values. Just don't use it.
     */
    Camera();


    Camera(const Vect &up, const Vect &right,
           const Vect &towards, const Point &focalPoint,
           const float fieldOfVision, const float viewPlaneDistance,
           const unsigned int width, const unsigned int height);

    /**
     * @return Middle Point of the upper-left most pixel in the image plane.
     */
    virtual Point GetFirstPixel() const = 0;

    /**
     * @return Up vector.
     */
    Vect GetUp() const;

    /**
     * @return Right vector.
     */
    Vect GetRight() const;

    /**
     * @return Towards vector.
     */
    Vect GetTowards() const;

    /**
     * @return Focal point, this Camera's position.
     */
    Point GetFocalPoint() const;

    /**
     * @return This Camera's image plane width in pixels.
     */
    unsigned int GetWidth() const;

    /**
     * @return This Camera's image plane height in pixels.
     */
    unsigned int GetHeight() const;

    /**
     * @return Pixel dimensions. Since they're squares both width and height are the same.
     */
    float GetPixelSize() const;

protected:

    /** This camera's vectors . */
    Vect mUp, mRight, mTowards;

    /** This camera's position. . */
    Point mFocalPoint;

    /** Field of view . */
    float mFoV;

    /** Distance from this Camera's position to the image plane. */
    float mViewPlaneDistance;

    /** Width and height in pixels for the image plane. */
    unsigned int mWidth, mHeight;

    /* Cached values. */

    /** Size of the pixels in the image plane . */
    float mPixelSize;

private:

    /**
     * Fills the field mPixelSize calculating the pixel size from the other parameters.
     */
    void CalculatePixelSize();
};

#endif // RAY_TRACER_CAMERA_HPP
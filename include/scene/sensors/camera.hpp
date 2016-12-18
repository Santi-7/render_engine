/** ---------------------------------------------------------------------------
 ** camera.hpp
 ** Abstract Camera for ray tracing. Must be defined for a scene to produce an image.
 ** The resulting image size is defined in the camera to allow traversing
 ** all the pixels that need tracing.
 ** From this camera we create a pinhole camera but we could extend it to be a
 ** fish eye camera or something else.
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

    /**
     * @return New Camera with default values. Just don't use it.
     */
    Camera();

    /**
     * Creates a new camera with the given parameters.
     *
     * @param up Vector that looks upwards of the camera focalPoint.
     * @param right Vector that looks to the right of the camera focalPoint.
     * @param towards Vector that looks to the front of the camera focalPoint.
     * @param focalPoint Center of the camera. Origin of all rays when tracing.
     * @param fieldOfVision Angle in radians the camera can see.
     * @param viewPlaneDistance Distance from the focalPoint to the image view plane,
     * @param width Width in pixels of the image view plane.
     * @param height Width in pixels of the image view plane.
     */
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
     * Sets this Camera's image width and height.
     *
     * @param width New width in pixels for the image plane in this camera.
     * @param height New height in pixels for the image plane in this camera.
     */
    void SetImageDimensions(unsigned int width, unsigned int height);

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

    /** This camera's vectors. */
    Vect mUp, mRight, mTowards;

    /** This camera's position. */
    Point mFocalPoint;

    /** Field of view. */
    float mFoV;

    /** Distance from this Camera's position to the image plane. */
    float mViewPlaneDistance;

    /** Width and height in pixels for the image plane. */
    unsigned int mWidth, mHeight;

    /* Cached values. */

    /** Size of the pixels in the image plane. */
    float mPixelSize;

private:

    /**
     * Fills the field mPixelSize calculating the pixel size from the other parameters.
     */
    void CalculatePixelSize();
};

#endif // RAY_TRACER_CAMERA_HPP
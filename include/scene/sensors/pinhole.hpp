/** ---------------------------------------------------------------------------
 ** pinhole.hpp
 ** The camera that will be used in the ray tracer.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_PINHOLE_HPP
#define RAY_TRACER_PINHOLE_HPP

#include <camera.hpp>
#include <image.hpp>
#include <lightRay.hpp>

class Pinhole : public Camera {

public:

    /**
     * @return Default Pinhole camera.
     */
    Pinhole();

    /**
     * @param up Vector for the up direction. Usually [0,1,0]
     * @param right Vector for the right direction. Usually [1, 0, 0]
     * @param towards Vector for the towards direction. Usually [0, 0, 1]
     * @param focalPoint Camera position. All rays traced will originate here.
     * @param fieldOfVision How wide an angle can be seen from the Camera.
     * @param viewPlaneDistance Distance from the Camera's position to the image Plane.
     * @param width Width of the image Plane in pixels.
     * @param height Height of the image Plane in pixels.
     * @return New Camera with the given parameters.
     */
    Pinhole(const Vect &up, const Vect &right,
            const Vect &towards, const Point &focalPoint,
            const float fieldOfVision, const float viewPlaneDistance,
            const unsigned int width, const unsigned int height);

    /**
     * @return Middle Point of the upper-left most pixel in the image plane.
     */
    Point GetFirstPixel() const;
};

#endif // RAY_TRACER_PINHOLE_HPP
/* ---------------------------------------------------------------------------
** pinhole.hpp
** TODO: Add doc.
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

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Pinhole();

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
    Pinhole(const Vect &up, const Vect &right,
            const Vect &towards, const Point &focalPoint,
            const float fieldOfVision, const float viewPlaneDistance,
            const unsigned int width, const unsigned int height);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Point GetFirstPixel() const;
};

#endif // RAY_TRACER_PINHOLE_HPP
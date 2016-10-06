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
     * @param focalPoint .
     * @param viewPlane .
     * @return .
     */
    Pinhole(Point focalPoint, Image viewPlane);

    // TODO: Add doc.
    /**
     * .
     *
     * @param x .
     * @param y .
     * @return .
     */
    LightRay PrimaryRay(const int x, const int y) const;

private:

    // TODO: Add doc.
    /* . */
    Image mImage;
};

#endif // RAY_TRACER_PINHOLE_HPP
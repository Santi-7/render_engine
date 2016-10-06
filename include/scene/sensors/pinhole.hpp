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

class Pinhole : public Camera {

public:
    Pinhole(Point focalPoint, Image viewPlane);

private:
    Image mImage;
};

#endif // RAY_TRACER_PINHOLE_HPP
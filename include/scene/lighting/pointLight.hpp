/* ---------------------------------------------------------------------------
** pointLight.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_POINT_LIGHT_HPP
#define RAY_TRACER_POINT_LIGHT_HPP

#include <lightSource.hpp>
#include <point.hpp>

class PointLight : public LightSource {

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    PointLight();

    // TODO: Add doc.
    /**
     * .
     *
     * @param position .
     * @return .
     */
    PointLight(const Point &position);

    // TODO: Add doc.
    /**
     * .
     *
     * @param position .
     * @param radiance .
     * @param baseColor .
     * @return .
     */
    PointLight(const Point &position, const float radiance,
               const Color &baseColor);

private:

    // TODO: Add doc.
    /* . */
    Point mPosition;
};

#endif // RAY_TRACER_POINT_LIGHT_HPP
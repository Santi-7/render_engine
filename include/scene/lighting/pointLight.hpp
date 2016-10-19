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

class PointLight : public LightSource
{

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
     * @param power .
     * @param baseColor .
     * @return .
     */
    PointLight(const Point &position, const float power, const Color &baseColor);

    // TODO: Add doc. Restriction: the point light must not be in a point of a shape.
    /**
     * .
     *
     * @param point .
     * @return .
     */
    Color GetColor(const Point &point) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    vector<Point> GetLights() const;

private:

    // TODO: Add doc.
    /* . */
    Point mPosition;
};

#endif // RAY_TRACER_POINT_LIGHT_HPP
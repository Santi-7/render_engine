/* ---------------------------------------------------------------------------
** pointLight.hpp
** Single point lightSource.
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

    /**
     * @return New white PointLight at [0,0,0] with power 2.0f.
     */
    PointLight();

    /**
     * @param position Position for the new PointLight.
     * @return New PointLight at position.
     */
    PointLight(const Point &position);

    /**
     * @param position Position for the new PointLight.
     * @param power Power for the new PointLight.
     * @param baseColor Color for the new PointLight.
     * @return New PointLight with the given position, power and color.
     */
    PointLight(const Point &position, const float power, const Color &baseColor);

    /**
     * If the point is too close to the PointLight the color returned will be too high. Make sure all shapes are
     * at a certain distance to all PointLights.
     *
     * @param point Point at which the light intensity will be calculated.
     * @return Color with the intensity of this light at point (the farther the point the smaller the intensity).
     */
    Color GetColor(const Point &point) const;

    /**
     * @return This PointLights position.
     */
    vector<Point> GetLights() const;

private:

    /** This PointLight's position. */
    Point mPosition;
};

#endif // RAY_TRACER_POINT_LIGHT_HPP
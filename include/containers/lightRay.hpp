/** ---------------------------------------------------------------------------
 ** lightRay.hpp
 ** This class will cause the intersections with shapes that ultimately render
 ** the image. A light ray is basically an origin point and a direction.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_LIGHT_RAY_HPP
#define RAY_TRACER_LIGHT_RAY_HPP

#include <point.hpp>

class LightRay
{

public:

    /**
     * Default constructor.
     */
    LightRay();

    /**
     * @param source The new light ray's origin.
     * @param destination Point towards which the new light ray will travel.
     * @return New LightRay.
     */
    LightRay(const Point &source, const Point &destination);

    /**
     * @param source The new light ray's origin.
     * @param direction Direction in which the new light ray will travel.
     * @return New LightRay.
     */
    LightRay(const Point &source, const Vect &direction);

    /**
     * @param t Distance from the origin.
     * @return New point at distance t from this lightRay's origin in its direction.
     */
    Point GetPoint(const float t) const;

    /**
     * @return This lightRay's origin point.
     */
    Point GetSource() const;

    /**
     * @return This lightRay's direction.
     */
    Vect GetDirection() const;

private:

    /** LightRay's origin. */
    Point mSource;

    /** LightRay's direction. */
    Vect mDirection;
};

#endif // RAY_TRACER_LIGHT_RAY_HPP
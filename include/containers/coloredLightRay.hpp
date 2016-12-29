/** ---------------------------------------------------------------------------
 ** coloredLightRay.hpp
 ** This class manages a ray of light with a defined color.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_COLOREDLIGHTRAY_HPP
#define RAY_TRACER_COLOREDLIGHTRAY_HPP

#include <color.hpp>
#include <lightRay.hpp>

class ColoredLightRay : public LightRay
{

public:

    /**
     * Default constructor.
     */
    ColoredLightRay();

    /**
     * TODO: Add doc.
     * @param source
     * @param direction
     * @param color
     * @return
     */
    ColoredLightRay(const Point &source, const Vect &direction, const Color &color);

    /**
     * @return This lightRay's color.
     */
    Color GetColor() const;

private:

    /** LightRay's color. */
    Color mColor;
};

#endif // RAY_TRACER_COLOREDLIGHTRAY_HPP

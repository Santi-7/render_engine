/* ---------------------------------------------------------------------------
** crossHatchModifier.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_CROSSHATCHMODIFIER_HPP
#define RAY_TRACER_CROSSHATCHMODIFIER_HPP

#include "vectorModifier.hpp"

class CrossHatchModifier : public VectorModifier {
public:
    CrossHatchModifier(float xDist, float yDist, float zDist);

    Vect Modify(const Vect &vect, const Point &point) const;

private:
    float mXDist, mYDist, mZDist;
};

#endif //RAY_TRACER_CROSSHATCHMODIFIER_HPP

/** ---------------------------------------------------------------------------
 ** crossHatchModifier.hpp
 ** Experimental modifier for normal vectors. Attempts to give shapes a different
 ** 3D texture, one that approximates, for instance, cloth or waves in a pond.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_CROSSHATCHMODIFIER_HPP
#define RAY_TRACER_CROSSHATCHMODIFIER_HPP

#include "vectorModifier.hpp"

class CrossHatchModifier : public VectorModifier {
public:

    /**
     * @param xDist Variation frequency for the x axis.
     * @param yDist Variation frequency for the y axis.
     * @param zDist Variation frequency for the z axis.
     * @return New CrossHatchModifier with the given values.
     */
    CrossHatchModifier(float xDist, float yDist, float zDist);

    /**
     * @param vect Vector to modify
     * @param point Point at which the modification will be calculated.
     * @return New Vector result of modifying vect with the variations in this modifier.
     */
    Vect Modify(const Vect &vect, const Point &point) const;

private:

    /** Values by which a normal at a point is modified. */
    float mXDist, mYDist, mZDist;
};

#endif //RAY_TRACER_CROSSHATCHMODIFIER_HPP

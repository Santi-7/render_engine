/* ---------------------------------------------------------------------------
** vectorModifier.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_NORMALMODIFIER_HPP
#define RAY_TRACER_NORMALMODIFIER_HPP

#include <vect.hpp>
#include <point.hpp>
#include <memory>

class VectorModifier {
public:
    virtual Vect Modify(const Vect &vect, const Point &point) const
    {
        return vect;
    }
};

#endif //RAY_TRACER_NORMALMODIFIER_HPP

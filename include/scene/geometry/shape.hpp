/* ---------------------------------------------------------------------------
** shape.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SHAPE_HPP
#define RAY_TRACER_SHAPE_HPP

#include <lightRay.hpp>
#include <materials/material.hpp>

class Shape
{

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @return .
     */
    virtual float Intersect(const LightRay &lightRay) const = 0;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param seenFrom .
     * @return .
     */
    virtual Vect GetVisibleNormal(const Point &point,
                                  const LightRay &seenFrom) const = 0;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    Material GetMaterial() const
    {
        return mMaterial;
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @param material .
     */
    void SetMaterial(const Material &material)
    {
        mMaterial = material;
    }

private:

    Material mMaterial;
};

#endif // RAY_TRACER_SHAPE_HPP
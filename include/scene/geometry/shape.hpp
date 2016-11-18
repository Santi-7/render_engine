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
#include <memory>

using namespace std;

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

    // TODO: Add doc
    /**
     *
     * @param lightRay
     * @param minT
     * @param nearestShape
     */
    virtual void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const = 0;

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
    shared_ptr<Material> GetMaterial() const
    {
        return mMaterial;
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @param material .
     */
    void SetMaterial(shared_ptr<Material> material)
    {
        mMaterial = material;
    }

private:

    shared_ptr<Material> mMaterial = DEFAULT_MATERIAL;
};

#endif // RAY_TRACER_SHAPE_HPP
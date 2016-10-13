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
//#include <material.hpp> TODO: Fix this.
#include <materials/material.hpp>

using namespace std;

class Shape {

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
     * @return .
     */
    virtual Vect GetNormal(const Point &point) const = 0;

    /**
     * .
     *
     * @return .
     */
    Material GetMaterial()
    {
        return mMaterial;
    }

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
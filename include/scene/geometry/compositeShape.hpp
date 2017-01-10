/** ---------------------------------------------------------------------------
 ** compositeShape.hpp
 ** Holds a list of shapes and a box that contains them to make rendering that
 ** much faster.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_COMPOSITESHAPE_HPP
#define RAY_TRACER_COMPOSITESHAPE_HPP

#include <materials/material.hpp>
#include <materials/vectorModifier.hpp>
#include <shape.hpp>
#include <vector>

class CompositeShape : public Shape
{

public:

    /**
     * Adds a shape to this CompositeShape.
     *
     * @tparam S Class of the shape.
     * @param shape Shape to add to this CompositeShape.
     */
    template <class S>
    void AddShape(const S &shape)
    {
        mShapesWithin.push_back(make_shared<S>(shape));
    }

    /**
     * Sets the bounding shape for this composite. The user has to make sure it's correct.
     *
     * @tparam S Class of the shape.
     * @param shape Shape to use as bounds for this composite.
     */
    template <class S>
    void SetBoundingShape(const S &shape)
    {
        mBoundingShape = make_shared<S>(shape);
    }

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to any of this shape points. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @param minT Minimum distance from the lightRay's origin to any shape so far. If this shape is closer to the origin
     *  than this value then it will be updated to that distance.
     * @param nearestShape Shape that is reportedly the closest to the lightRay's origin so far. Updated to thisShape
     *  if this shape is at a distance from the lightRay's origin smaller than minT and this shape doesn't contain any
     *  sub-shapes.
     * @param thisShape shared_ptr to this shape.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                   shared_ptr<Shape> thisShape) const;

    /**
     * This method is not usable for this shape. Calling it will result in an exception. This is because a CompositeShape
     * may not have volume, and no point can be inside it.
     */
    bool IsInside(const Point &point) const { throw 1; }

    /**
     * Don't use this, call it for each individual shape in this container
     */
    Vect GetNormal(const Point &point) const { throw 1; }

    /**
     * Don't use this, call it for each individual shape in this container
     */
    void SetMaterial(const shared_ptr<Material> material) { throw 1; }

    /**
     * Don't use this, call it for each individual shape in this container
     */
    void SetNormalModifier(shared_ptr<VectorModifier> vmod) { throw 1; }

private:

    vector<shared_ptr<Shape>> mShapesWithin;
    shared_ptr<Shape> mBoundingShape;
};

#endif // RAY_TRACER_COMPOSITESHAPE_HPP
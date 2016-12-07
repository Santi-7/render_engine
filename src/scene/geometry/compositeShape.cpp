/** ---------------------------------------------------------------------------
 ** compositeShape.cpp
 ** Implement compositeShape class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <compositeShape.hpp>
#include <cfloat>

float CompositeShape::Intersect(const LightRay& lightRay) const
{
    if (mBoundingShape->Intersect(lightRay) != FLT_MAX)
    {
        for (const shared_ptr<Shape> &shape : mShapesWithin)
        {
            float tmpT;
            tmpT = shape->Intersect(lightRay);
            if (tmpT < FLT_MAX) return tmpT;
        }
    }
    return FLT_MAX;
}

void CompositeShape::Intersect(const LightRay& lightRay, float& minT, shared_ptr <Shape>& nearestShape,
        shared_ptr <Shape> thisShape) const
{
    if (mBoundingShape->Intersect(lightRay) != FLT_MAX)
    {
        for (const shared_ptr<Shape> &shape : mShapesWithin)
        {
            shape->Intersect(lightRay, minT, nearestShape, shape);
        }
    }
}

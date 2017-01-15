/** ---------------------------------------------------------------------------
 ** box.hpp
 ** Class containing a box made out of 6 rectangles.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_BOX_HPP
#define RAY_TRACER_BOX_HPP

#include <rectangle.hpp>

class Box : public Shape
{

public:

    /**
     * @param base Base for the new box. It doesn't need to have the minimum y value, it can be any of a box's faces.
     * @param depth How much to extrude the base to form the new box.
     * @return New box formed by extruding the base by depth (in the direction normal to the base).
     */
    Box(const Rectangle &base, const float depth);

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to any of this box's faces. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @param minT Minimum distance from the lightRay's origin to any shape so far. If this shape is closer to the origin
     *  than this value then it will be updated to that distance.
     * @param nearestShape Shape that is reportedly the closest to the lightray's origin so far. If any of the rectangles
     * in this box is closer then it will be updated to that rectangle's pointer.
     * @param thisShape Unused.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                   shared_ptr<Shape> thisShape) const;

    /**
     * @param point Point to determine if it's inside this Box.
     * @return true if the point is inside this Box, false otherwise.
     */
    bool IsInside(const Point &point) const;

    /**
     * This method is not usable for this shape since it makes no sense for it to have a normal.
     */
    Vect GetNormal(const Point &point) const;

    /**
     * Sets the material of all the faces in this box to material.
     * @param material for every face in this box.
     */
    void SetMaterial(shared_ptr<Material> material);

    /**
     * Sets the material of all the faces in this box to material.
     * @tparam M Any material type.
     * @param material for every face in this box.
     */
    template <class M>
    void SetMaterial(M material)
    {
        for (const shared_ptr<Rectangle> &face : mFaces)
        {
            face->SetMaterial(material);
        }
    }

    /**
     * Sets the normal modifier of all the faces in this box to vmod.
     * @param vmod Normal modifier for all the faces in this box.
     */
    void SetNormalModifier(shared_ptr<VectorModifier> vmod);

    /**
     * Sets the refractive index of this shape.
     *
     * @param refractiveIndex Value to set the refractive index of this shape.
     */
    void SetRefractiveIndex(const float refractiveIndex);

protected:

    /** The six faces of this box. */
    array<shared_ptr<Rectangle>, 6> mFaces;
};

#endif //RAY_TRACER_BOX_HPP
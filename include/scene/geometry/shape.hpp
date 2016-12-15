/** ---------------------------------------------------------------------------
 ** shape.hpp
 ** Abstract definition for 3D shapes. Defines common methods for setting values
 ** such as material or refractive index and leaves some to be defined by its
 ** children.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SHAPE_HPP
#define RAY_TRACER_SHAPE_HPP

#include <cmath>
#include <lightRay.hpp>
#include <materials/material.hpp>
#include <memory>
#include <mathConstants.hpp>
#include <visibleNormal.hpp>
#include <materials/vectorModifier.hpp>

using namespace std;

class Shape
{

public:

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to any of this shape points. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    virtual float Intersect(const LightRay &lightRay) const = 0;

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @param minT Minimum distance from the lightRay's origin to any shape so far. If this shape is closer to the origin
     *  than this value then it will be updated to that distance.
     * @param nearestShape Shape that is reportedly the closest to the lightRay's origin so far. Updated to thisShape
     *  if this shape is at a distance from the lightRay's origin smaller than minT and this shape doesn't contain any
     *  sub-shapes.
     * @param thisShape shared_ptr to this shape.
     */
    virtual void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const = 0;

    /**
     * Based on http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf.
     *
     * @param in LightRay entering this shape.
     * @param point Point at which in enters this shape.
     * @param visibleNormal Normal for this shape at point.
     * @return New lightRay refracted from in with origin point.
     */
    LightRay Refract(const LightRay &in, const Point &point, const Vect &visibleNormal) const
    {
        // TODO: Temporal implementation. A lightray should contain a stack of the passing mediums.
        float n;
        // The ray of light is arriving the shape medium.
        if (visibleNormal == GetNormal(point))
        {
            n = mN;
        }
        // The ray of light is exiting the shape medium.
        else
        {
            n = 1 / mN;
        }
        // Calculate the refracted ray of light.
        float cosI = -visibleNormal.DotProduct(in.GetDirection());
        float sinT2 = n * n * (1 - cosI * cosI);
        // Critic angle: this is the angle at which the refracted lightRay goes back inside the shape.
        if (sinT2 > 1)
            // TODO: Reflect the ray.
            ;
        float cosT = sqrt(1 - sinT2);
        Vect reflected = in.GetDirection() * n + visibleNormal * (n * cosI - cosT);
        return LightRay(point, reflected);
    }

    /**
     * @param point Point of this shape which normal vector will be returned.
     * @return Vector normal to this shape at point.
     */
    virtual Vect GetNormal(const Point &point) const = 0;

    /**
     * @param point Point of this shape which normal vector will be returned.
     * @param seenFrom LightRay from which this shape is seen.
     * @return Vector normal to this shape at point in a direction opposite from seenFrom. For instance, if this shape
     *  is a rectangle we could be seeing it from the two sides of it and their normals are opposite.
     */
    Vect GetVisibleNormal(const Point &point, const LightRay &seenFrom)
    {
        if (mNormalModifier != nullptr)
            return mNormalModifier->Modify(VisibleNormal(GetNormal(point), seenFrom.GetDirection()), point);
        else
            return VisibleNormal(GetNormal(point), seenFrom.GetDirection());
    }

    /**
     * @return Pointer to the material in this shape.
     */
    shared_ptr<Material> GetMaterial() const
    {
        return mMaterial;
    }

    /**
     * Sets the material in this shape. If this shape contains any sub-shapes they should also have their materials set
     * to material by overriding this method.
     * @param material Material for this shape.
     */
    virtual void SetMaterial(const shared_ptr<Material> material)
    {
        mMaterial = material;
    }

    /**
     * Creates a new shared_ptr to the material of class M and sets it to this class.
     * @tparam M Class of the material.
     * @param material Material for this shape.
     */
    template <class M>
    void SetMaterial(const M material)
    {
        mMaterial = make_shared<M>(material);
    }

    /**
     * Sets the refractive index of this shape. If this shape contains any sub-shapes they should also have their
     * materials set to material by overriding this method (Since refraction doesn't take into account materials other
     * than spheres this won't happen). // TODO: Check that later fact when finishing up.
     * @param refractiveIndex Value to set the refractive index of this shape.
     */
    void SetRefractiveIndex(const float refractiveIndex)
    {
        mN = refractiveIndex;
    }

    /**
     * @return Emitted light as a color
     */
    Color GetEmittedLight()
    {
        return mEmitted * mPowerEmitted;
    }

    /**
     * Sets the emitted color value and marks this shape as a light source
     * @param emitted .
     * @param power .
     */
    void SetEmittedLight(const Color &emitted, const float power)
    {
        mEmitted = emitted;
        mPowerEmitted = power;
        SetMaterial(NONE);
    }

    /**
     * Sets the normal modifier for this shape. This is an experimental feature...
     * @param vmod Normal modifier for this shape.
     */
    virtual void SetNormalModifier(shared_ptr<VectorModifier> vmod)
    {
        mNormalModifier = vmod;
    }

private:

    /** Pointer to the material in this shape . */
    shared_ptr<Material> mMaterial = LAMBERTIAN;

    /** This shape's refractive index. */
    refractiveIndex mN = AIR_RI;

    /** This shape's normal vector modifier. Again, this is an experimental feature.*/
    shared_ptr<VectorModifier> mNormalModifier = nullptr;

    /** Color emitted by this shape. */
    Color mEmitted = BLACK;

    /** Power of the color emmited. */
    float mPowerEmitted = 0.0f;
};

#endif // RAY_TRACER_SHAPE_HPP
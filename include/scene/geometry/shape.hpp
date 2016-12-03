/* ---------------------------------------------------------------------------
** shape.hpp
** TODO: Add doc.
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

    // TODO: Add doc
    /**
     * .
     *
     * Based on http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf.
     *
     * @param in .
     * @param point .
     * @param visibleNormal .
     * @return .
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
        if (sinT2 > 1)
            // Error.
            // TODO: Check what to do here.
            ;
        float cosT = sqrt(1 - sinT2);
        Vect reflected = in.GetDirection() * n + visibleNormal * (n * cosI - cosT);
        return LightRay(point, reflected);
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @return .
     */
    virtual Vect GetNormal(const Point &point) const = 0;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param seenFrom .
     * @return .
     */
    Vect GetVisibleNormal(const Point &point, const LightRay &seenFrom)
    {
        if (mNormalModifier != nullptr)
            return mNormalModifier->Modify(VisibleNormal(GetNormal(point), seenFrom.GetDirection()), point);
        else
            return VisibleNormal(GetNormal(point), seenFrom.GetDirection());
    }

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
    virtual void SetMaterial(const shared_ptr<Material> material)
    {
        mMaterial = material;
    }

    template <class M>
    void SetMaterial(const M material)
    {
        mMaterial = make_shared<M>(material);
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @param material .
     */
    void SetRefractiveIndex(const float refractiveIndex)
    {
        mN = refractiveIndex;
    }

    bool IsLightSource()
    {
        return mIsLightSource;
    }

    Color GetEmmitedLight()
    {
        return mEmitted;
    }

    /**
     * Sets the emmited color value and marks this shape as a light source
     * @param emmited
     */
    void SetEmittedLight(const Color &emmited)
    {
        mEmitted = emmited;
        mIsLightSource = true;
    }

    virtual void SetNormalModifier(shared_ptr<VectorModifier> vmod)
    {
        mNormalModifier = vmod;
    }

private:

    // TODO: Add doc.
    /* . */
    shared_ptr<Material> mMaterial = LAMBERTIAN;

    // TODO: Add doc.
    /* . */
    refractiveIndex mN = AIR_RI;

    shared_ptr<VectorModifier> mNormalModifier = nullptr;

    Color mEmitted = Color(0.0f,0.0f,0.0f);

    bool mIsLightSource = false;
};

#endif // RAY_TRACER_SHAPE_HPP
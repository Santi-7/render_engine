/* ---------------------------------------------------------------------------
** material.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <material.hpp>
#include <math.h>
#include <mathConstants.hpp>

Material::Material()
: mKd(1.0f), mKs(0.0f), mAlpha(20.0f), mKr(0.0f), mKt(0.0f)
{}

Material::Material(const float diffuse, const float specular,
                   const float alpha, const float reflectance,
                   const float transparent)
: mKd(diffuse), mKs(specular), mAlpha(alpha), mKr(reflectance), mKt(transparent)
{}

float Material::PhongBRDF(const Vect &seenFrom, const Vect &light) const
{
    // Using local coordinates.
    Vect reflected = Vect(-light.GetX(), -light.GetY(), light.GetZ());
    float cosine = seenFrom.DotProduct(reflected);
    return (mKd / PI) + mKs * (mAlpha + 2) / (2 * PI) * pow(cosine, mAlpha);
}

float Material::GetReflectance() const
{
    return mKr;
}
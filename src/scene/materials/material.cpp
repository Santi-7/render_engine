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
: mKd(GRAY), mKs(BLACK),
  mKr(BLACK), mKt(BLACK), mShininess(0.0f)
{}

Material::Material(const Color diffuse, const Color specular,
                   const float shininess, const Color reflectance,
                   const Color transmittance)
: mKd(diffuse), mKs(specular), mKr(reflectance),
  mKt(transmittance), mShininess(shininess)
{}

Color Material::PhongBRDF(const Vect &seenFrom, const Vect &light,
                          const Vect &normal, const Point &point) const
{
    // TODO: Change to global method.
    Vect reflected = light- normal * light.DotProduct(normal) * 2;
    float cosine = seenFrom.DotProduct(reflected);
    return (this->GetDiffuse(point) / PI) + mKs * (mShininess + 2) / (2 * PI) * pow(cosine, mShininess);
}

Color Material::GetDiffuse() const
{
    return mKd;
}

Color Material::GetDiffuse(const Point &point) const
{
    return mKd;
}

Color Material::GetReflectance() const
{
    return mKr;
}

Color Material::GetTransmittance() const
{
    return mKt;
}
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
: mKd(1.0f), mKs(0.0f), mShininess(20.0f), mKr(0.0f), mKt(0.0f)
{}

Material::Material(const float diffuse, const float specular,
                   const float shininess, const float reflectance,
                   const float transmittance)
: mKd(diffuse), mKs(specular), mShininess(shininess),
  mKr(reflectance), mKt(transmittance)
{}

float Material::PhongBRDF(const Vect &seenFrom, const Vect &light,
                          const Vect &normal) const
{
    // TODO: Change to global method.
    Vect reflected = light- normal * light.DotProduct(normal) * 2;
    float cosine = seenFrom.DotProduct(reflected);
    return (mKd / PI) + mKs * (mShininess + 2) / (2 * PI) * pow(cosine, mShininess);
}

float Material::GetDiffuse() const
{
    return mKd;
}

float Material::GetReflectance() const
{
    return mKr;
}

float Material::GetTransmittance() const
{
    return mKt;
}
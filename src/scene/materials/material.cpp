/* ---------------------------------------------------------------------------
** material.cpp
** Implementation for Material class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <material.hpp>
#include <math.h>
#include <mathConstants.hpp>
#include <shape.hpp>

Material::Material(const Color diffuse, const Color specular,
                   const float shininess, const Color reflectance,
                   const Color transmittance)
: mKd(diffuse), mKs(specular), mKr(reflectance),
  mKt(transmittance), mShininess(shininess)
{}

Color Material::PhongBRDF(const Vect &seenFrom, const Vect &light,
                          const Vect &normal, const Point &point) const
{
    Vect reflectedLight = Shape::Reflect(light * -1, normal);
    float cosine = seenFrom.DotProduct(reflectedLight);
    if (cosine < 0) cosine = 0;

    return (this->GetDiffuse(point) / PI) + mKs * ((mShininess + 2) / (2 * PI) * pow(cosine, mShininess));
}

Color Material::GetDiffuse(const Point &point) const
{
    return mKd;
}

Color Material::GetSpecular() const
{
    return mKs;
}

Color Material::GetReflectance() const
{
    return mKr;
}

Color Material::GetTransmittance() const
{
    return mKt;
}
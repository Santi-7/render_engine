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
: mKr(0.0f)
{}

Material::Material(const float reflectance)
: mKr(reflectance)
{}

float Material::PhongBRDF(const Vect &in, const Vect &out) const
{
    // Using local coordinates.
    Vect reflected = Vect(-out.GetX(), -out.GetY(), out.GetZ());
    float cosine = in.DotProduct(reflected);
    return (mKd / PI) + mKs * (mAlfa + 2) / (2 * PI) * pow(cosine, mAlfa);
}

float Material::GetReflectance() const
{
    return mKr;
}
/* ---------------------------------------------------------------------------
** material.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <material.hpp>

Material::Material()
: mReflectance(0.0f)
{}

Material::Material(const float reflectance)
: mReflectance(reflectance)
{}

float Material::GetReflectance() const
{
    return mReflectance;
}

bool Material::IsReflective() const
{
    return mReflectance != 0.0;
}
/* ---------------------------------------------------------------------------
** material.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <material.hpp>

Material::Material() : Material(0.0f) {}

Material::Material(float reflectance) : mReflectance(reflectance) {}

float Material::GetReflectance()
{
    return mReflectance;
}

bool Material::IsReflective()
{
    return mReflectance != 0.0;
}
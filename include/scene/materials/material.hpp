/* ---------------------------------------------------------------------------
** material.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

#include <vect.hpp>

class Material
{

public:

    // TODO: Add doc.
    /**
     * Creates a Lambertian material.
     *
     * @return Lambertian material.
     */
    Material();

    // TODO: Add doc.
    /**
     * Creates a material with the given reflectance.
     *
     * @param reflectance for this material.
     * @return New material with the given reflectance.
     */
    Material(const float reflectance);

    // TODO: Add doc.
    /**
     * .
     *
     * @param in .
     * @param out .
     * @return .
     */
    float PhongBRDF(const Vect &in, const Vect &out) const;

    // TODO: Add doc.
    /**
     * Returns this material's reflectance.
     *
     * @return Reflectance of this material
     */
    float GetReflectance() const;

private:

    // TODO: Add doc.
    /* . */
    float mKd, mKs, mAlfa, mKr, mKt;
};

#endif //RAY_TRACER_MATERIAL_HPP

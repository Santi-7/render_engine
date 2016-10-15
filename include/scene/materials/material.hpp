/* ---------------------------------------------------------------------------
** material.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

class Material {

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
     * Returns this material's reflectance.
     *
     * @return Reflectance of this material
     */
    float GetReflectance() const;

    // TODO: Add doc.
    /**
     * True if this material's reflectance is not zero.
     *
     * @return True if this material's reflectance
     *         is not zero, false otherwise.
     */
    bool IsReflective() const;

private:

    float mReflectance;
};

#endif //RAY_TRACER_MATERIAL_HPP

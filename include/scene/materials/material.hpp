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
#include <memory>

using namespace std;

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
    Material(const float diffuse, const float specular,
             const float alpha, const float reflectance, const float trans);

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
    float mKd, mKs, mAlpha, mKr, mKt;
};

static const shared_ptr<Material> DEFAULT_MATERIAL = make_shared<Material>(Material());

static const shared_ptr<Material> MIRROR = make_shared<Material>(Material(0, 0, 0, 1, 0));
static const shared_ptr<Material> LAMBERTIAN = make_shared<Material>(Material(1, 0, 0, 0, 0));
static const shared_ptr<Material> SPECKLED_LAMBERTIAN = make_shared<Material>(Material(1, 1, 0, 0, 0));
//static const shared_ptr<Material> GLASS = make_shared<Material>(Material(0,0,0,0,1));

#endif //RAY_TRACER_MATERIAL_HPP

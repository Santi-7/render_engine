/* ---------------------------------------------------------------------------
** material.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

#include <memory>
#include <vect.hpp>

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
     * @param diffuse .
     * @param specular .
     * @param shininess .
     * @param reflectance for this material.
     * @param transmittance .
     * @return New material with the given .
     */
    Material(const float diffuse, const float specular,
             const float shininess, const float reflectance,
             const float transmittance);

    // TODO: Add doc.
    /**
     * .
     *
     * @param seenFrom .
     * @param light .
     * @param normal .
     * @return .
     */
    float PhongBRDF(const Vect &seenFrom, const Vect &light,
                    const Vect &normal) const;

    // TODO: Add doc.
    /**
     * Returns this material's reflectance.
     *
     * @return Reflectance of this material.
     */
    float GetReflectance() const;

    // TODO: Add doc.
    /**
     * Returns this material's transmittance.
     *
     * @return Transmittance of this material.
     */
    float GetTransmittance() const;

private:

    // TODO: Add doc.
    /* . */
    float mKd, mKs, mShininess, mKr, mKt;
};

static const shared_ptr<Material> DEFAULT_MATERIAL = make_shared<Material>(Material());
static const shared_ptr<Material> MIRROR = make_shared<Material>(Material(0, 0, 0, 1, 0));
static const shared_ptr<Material> LAMBERTIAN = make_shared<Material>(Material(1, 0, 0, 0, 0));
static const shared_ptr<Material> SPECKLED_LAMBERTIAN = make_shared<Material>(Material(1, 1, 0, 0, 0));
static const shared_ptr<Material> GLASS = make_shared<Material>(Material(0,0,0,0,1));

#endif // RAY_TRACER_MATERIAL_HPP
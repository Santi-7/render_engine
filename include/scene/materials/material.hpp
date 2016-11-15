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
#include <color.hpp>

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
    Material(const Color diffuse, const Color specular,
             const float shininess, const Color reflectance,
             const Color transmittance);

    // TODO: Add doc.
    /**
     * .
     *
     * @param seenFrom .
     * @param light .
     * @param normal .
     * @return .
     */
    Color PhongBRDF(const Vect &seenFrom, const Vect &light,
                    const Vect &normal) const;

    // TODO: Add doc.
    /**
     * Returns this material's .
     *
     * @return  of this material.
     */
    Color GetDiffuse() const;

    // TODO: Add doc.
    /**
     * Returns this material's reflectance.
     *
     * @return Reflectance of this material.
     */
    Color GetReflectance() const;

    // TODO: Add doc.
    /**
     * Returns this material's transmittance.
     *
     * @return Transmittance of this material.
     */
    Color GetTransmittance() const;

private:

    // TODO: Add doc.
    /* . */
    Color mKd, mKs, mKr, mKt;

    // TODO: Add doc.
    /* . */
    float mShininess;
};

static const shared_ptr<Material> DEFAULT_MATERIAL = make_shared<Material>(Material());
static const shared_ptr<Material> MIRROR = make_shared<Material>(Material(BLACK, BLACK, 0, WHITE, BLACK));
static const shared_ptr<Material> LAMBERTIAN = make_shared<Material>(Material(WHITE, BLACK, 0, BLACK, BLACK));
static const shared_ptr<Material> SPECKLED_LAMBERTIAN = make_shared<Material>(Material(WHITE, WHITE, 0, BLACK, BLACK));
static const shared_ptr<Material> GLASS = make_shared<Material>(Material(BLACK,BLACK,0,BLACK,GRAY));

#endif // RAY_TRACER_MATERIAL_HPP
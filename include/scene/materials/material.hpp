/** ---------------------------------------------------------------------------
 ** material.hpp
 ** General material for use in 3D shapes. Contains the diffuse, specular,
 ** reflectance, transmittance and shininess values needed for simulating
 ** different materials.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

#include <color.hpp>
#include <memory>
#include <point.hpp>
#include <vect.hpp>

using namespace std;

class Material
{

public:

    /**
     * Creates a material with the given reflectance.
     *
     * @param diffuse kD for the new Material.
     * @param specular kS for the new Material.
     * @param shininess shininess for the new Material.
     * @param reflectance kR for the new Material.
     * @param transmittance kT for the new Material.
     * @return New material with the given values.
     */
    Material(const Color diffuse, const Color specular,
             const float shininess, const Color reflectance,
             const Color transmittance);

    /**
     * Returns the color for the given parameters following a corrected Phong's BRDF.
     *
     * @param seenFrom Direction from which the color is calculated.
     * @param light Direction of the incoming light.
     * @param normal Normal to the surface.
     * @param point Point in which the light incedes.
     * @return Color resulting of Phong's corrected BRDF for the given values.
     */
    Color PhongBRDF(const Vect &seenFrom, const Vect &light,
                    const Vect &normal, const Point &point) const;

    /**
     * @return kD value for this material.
     */
    Color GetDiffuse() const;

    /**
     * @param point Point for which the diffuse value is returned.
     * @return kD value for this material at the given point.
     */
    virtual Color GetDiffuse(const Point &point) const;

    /**
     * @return kR value for this material.
     */
    Color GetReflectance() const;

    /**
     * @return kT value for this material.
     */
    Color GetTransmittance() const;

private:

    /** Color and physical properties for this material. */
    Color mKd, mKs, mKr, mKt;

    /** How shiny this material is. */
    float mShininess;
};

/** Common material definitions to make materials easier to use down the line. */
static const shared_ptr<Material> MIRROR = make_shared<Material>(Material(BLACK, BLACK, 0, WHITE, BLACK));
static const shared_ptr<Material> LAMBERTIAN = make_shared<Material>(Material(GRAY, BLACK, 0, BLACK, BLACK));
static const shared_ptr<Material> SPECKLED_LAMBERTIAN = make_shared<Material>(Material(GRAY, GRAY, 20, BLACK, BLACK));
static const shared_ptr<Material> GLASS = make_shared<Material>(Material(BLACK,BLACK,0,BLACK,WHITE));

#endif // RAY_TRACER_MATERIAL_HPP
/** ---------------------------------------------------------------------------
 ** photon.hpp
 ** Simple class containing all the information needed to represent a simple photon.
 ** The representation is simple as in not phisically correct since a photon will
 ** simply be of one of the three primary colors of light instead of a wavelength.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/
#ifndef RAY_TRACER_PHOTON_HPP
#define RAY_TRACER_PHOTON_HPP

#include <coloredLightRay.hpp>
#include <vect.hpp>

class Photon
{
public:

    /**
     * Default constructor.
     */
    Photon();

    /**
     * Constructor of a photon for the given flux and incidence vector values.
     *
     * @param flux Flux of this photon, defined as its RGB value.
     * @param incidence Vector that marks the direction from which this photon has come.
     */
    Photon(const Color &flux, const Vect &incidence);

    /**
     * TODO: Add doc.
     * @param lightRay
     * @return
     */
    Photon(const ColoredLightRay &lightRay);

    /**
     * @return Direction in which this photon was last stored.
     */
    Vect GetVect();

    /**
     * @return This Photon's flux.
     */
    Color GetFlux();
    
private:

    /** Color representing the energy left in a Photon. */
    Color mFlux;

    /** Direction from which a Photon strikes the surface in the instant its stored. */
    Vect mIncidence;
};

#endif // RAY_TRACER_PHOTON_HPP
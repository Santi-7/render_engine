/** ---------------------------------------------------------------------------
 ** photon.cpp
 ** Implementation for Photon class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <photon.hpp>

Photon::Photon() {}

Photon::Photon(const Color& flux, const Vect &incidence)
: mFlux(flux), mIncidence(incidence)
{}

Photon::Photon(const ColoredLightRay &lightRay)
: Photon(lightRay.GetColor(), lightRay.GetDirection())
{}

Vect Photon::GetVect()
{
    return mIncidence;
}

Color Photon::GetFlux()
{
    return mFlux;
}
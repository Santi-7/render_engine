/** ---------------------------------------------------------------------------
 ** photon.cpp
 ** Implementation for Photon class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <photon.hpp>
#include <color.hpp>
#include <vect.hpp>

Photon::Photon(const Color& flux, Vect incidence) : mFlux(flux), mIncidence(incidence){}

Vect Photon::GetVect()
{
    return mIncidence;
}

Color Photon::GetFlux()
{
    return mFlux;
}

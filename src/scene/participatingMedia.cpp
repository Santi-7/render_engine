/** ---------------------------------------------------------------------------
 ** participatingMedia.cpp
 ** Implementation for ParticipatingMedia class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <participatingMedia.hpp>

ParticipatingMedia::ParticipatingMedia(const shared_ptr<Shape> &shape,
                                       const float scattering, const float absorption)
: mShape(shape), mKs(scattering), mKa(absorption),
  mKt(scattering + absorption), mMeanFreePath(1 / mKt)
{}

float ParticipatingMedia::GetTransmittance(const Point &from, const Point &to) const
{
    return exp(-mKt * from.Distance(to));
}
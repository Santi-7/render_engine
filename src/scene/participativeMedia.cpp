/* ---------------------------------------------------------------------------
** participativeMedia.cpp
** Implementation for ParticipativeMedia class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <participativeMedia.hpp>

ParticipativeMedia::ParticipativeMedia(const Shape &shape, const float scattering, const float absorption)
: mShape(make_shared<Shape>(shape)), mKs(scattering), mKa(absorption),
  mKt(scattering + absorption), mMeanFreePath(1 / mKt)
{}

float ParticipativeMedia::GetTransmittance(const Point &from, const Point &to) const
{
    return exp(-mKt * from.Distance(to));
}
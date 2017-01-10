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

void ParticipatingMedia::Intersect(const LightRay &lightRay, float &minT) const
{
    shared_ptr<Shape> patch;
    return mShape->Intersect(lightRay, minT, patch, nullptr);
}

float ParticipatingMedia::GetTransmittance(const Point &from, const Point &to) const
{
    return exp(-mKt * from.Distance(to));
}

bool ParticipatingMedia::IsInside(const Point &point) const
{
    return mShape->IsInside(point);
}
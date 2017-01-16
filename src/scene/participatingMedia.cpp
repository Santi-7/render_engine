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
  mKt(scattering + absorption), mMeanFreePath(1 / mKt),
  mAlbedo(mKs / mKt)
{}

void ParticipatingMedia::Intersect(const LightRay &lightRay, float &minT) const
{
    shared_ptr<Shape> patch;
    return mShape->Intersect(lightRay, minT, patch, nullptr);
}

float ParticipatingMedia::GetTransmittance(const float distance) const
{
    return exp(-mKt * distance);
}

float ParticipatingMedia::GetNextInteraction() const
{
    // Randomize the step, but in mean we get the mean-free path.
    return GetRandomValue() * 2 * mMeanFreePath;
}

bool ParticipatingMedia::IsInside(const Point &point) const
{
    return mShape->IsInside(point);
}

bool ParticipatingMedia::RussianRoulette(const ColoredLightRay &in,
                                         const Point &point, ColoredLightRay &out) const
{
    float random = GetRandomValue();
    // The event is scattering;
    if (random < mAlbedo)
    {
        /* Transformation matrix from the local coordinates with [point] as the
         * reference point, and the incoming lightray as the z axis, to global coordinates. */
        PoseTransformationMatrix fromLocalToGlobal =
                PoseTransformationMatrix::GetPoseTransformation(point, in.GetDirection());
        // Generate random angles in the sphere.
        float inclination, azimuth;
        tie(inclination, azimuth) = UniformSphereSampling();
        // Direction of the ray of light expressed in local coordinates.
        Vect localRay(sin(inclination) * cos(azimuth),
                      sin(inclination) * sin(azimuth),
                      cos(inclination));
        // Transform the ray of light to global coordinates.
        out = ColoredLightRay(point, fromLocalToGlobal * localRay,
                              in.GetColor() / mAlbedo / PHASE_FUNCTION);
        return true;
    }
    // The event is absorption;
    else return false;
}

float ParticipatingMedia::GetScattering() const
{
    return mKs;
}
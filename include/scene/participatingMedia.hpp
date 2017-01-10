/** ---------------------------------------------------------------------------
 ** participatingMedia.hpp
 ** Represents a participating media (fog, smoke...) Only homogeneus and
 ** isotropic participating media are supported.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_PARTICIPATINGMEDIA_HPP
#define RAY_TRACER_PARTICIPATINGMEDIA_HPP

#include <shape.hpp>

class ParticipatingMedia
{

public:

    /**
     * @param shape Shape that wraps the participating media. Note: It should be a shape
     *  with volume, i.e. boxes and spheres.
     * @param scattering Scattering coefficient.
     * @param absorption Absorption coefficient.
     * @return New ParticipatingMedia with given scattering and absorption coefficients.
     */
    ParticipatingMedia(const shared_ptr<Shape> &shape, const float scattering, const float absorption);

    /**
     * @param lightRay Contains the point from which an intersection with this media will measured.
     * @param minT Minimum distance from the lightRay's origin to any media so far. If this media is closer to the origin
     *  than this value then it will be updated to that distance.
     */
    void Intersect(const LightRay &lightRay, float &minT) const;

    /**
     * @param from Source point of the segment where transmittance is calculated..
     * @param to Destination point of the segment where transmittance is calculated.
     * @return Transmittance from the point [from] to the point [to] in this media.
     */
    float GetTransmittance(const Point &from, const Point &to) const;

private:

    /** Shape that wraps the participang media.
     * Note: It should be a shape with volume, i.e. boxes, spheres. */
    shared_ptr<Shape> mShape;

    /** Scattering coefficient that defines the media. */
    float mKs;

    /** Absorption coefficient that defines the media. */
    float mKa;

    /* Cached values. */

    /** Extinction coefficient. */
    float mKt;

    /** Mean free path of the media. */
    float mMeanFreePath;
};

#endif // RAY_TRACER_PARTICIPATINGMEDIA_HPP
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

    /** Phase function in any point in any direction of the media. Const value because
     * only and isotropic media are supported. */
    constexpr static float PHASE_FUNCTION = 1 / (4 * PI);

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
     * @param distance Distance though transmittance is calculated
     * @return Transmittance through [distance] in this media.
     */
    float GetTransmittance(const float distance) const;

    /**
     * TODO: Add doc.
     * @return .
     */
    float GetNextInteraction() const;

    /**
     * @param point Point to determine if it's inside this media.
     * @return true if the point is inside this media, false otherwise.
     */
    bool IsInside(const Point &point) const;

    /**
     * @param in LightRay that is directed inside the media.
     * @param point Point in which the LightRay interacts with the media (mean-free path).
     * @param out When the return value of this method is true this value is updated to the LightRay result
     *  of the interaction with the media at the given point.
     * @return True if a new LightRay comes out of the interaction with this media, false otherwise, when
     *  the LightRay is absorbed.
     */
    bool RussianRoulette(const ColoredLightRay &in, const Point &point, ColoredLightRay &out) const;

    /**
     * @return Scattering coefficient of this media.
     */
    float GetScattering() const;

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

    /** Albedo of the media. */
    float mAlbedo;
};

#endif // RAY_TRACER_PARTICIPATINGMEDIA_HPP
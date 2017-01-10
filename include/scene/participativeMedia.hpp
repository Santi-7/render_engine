/** ---------------------------------------------------------------------------
 ** participativeMedia.hpp
 ** Represents a participative media (fog, smoke...) Only homogeneus and
 ** isotropic participative media are supported.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_PARTICIPATIVEMEDIA_HPP
#define RAY_TRACER_PARTICIPATIVEMEDIA_HPP

#include <shape.hpp>

class ParticipativeMedia
{

public:

    /**
     * @param shape Shape that wraps the participative media. Note: It should be a shape
     *  with volume, i.e. boxes and spheres.
     * @param scattering Scattering coefficient.
     * @param absorption Absorption coefficient.
     * @return New ParticipativeMedia with given scattering and absorption coefficients.
     */
    ParticipativeMedia(const Shape &shape, const float scattering, const float absorption);

    /**
     * @param from Source point of the segment where transmittance is calculated..
     * @param to Destination point of the segment where transmittance is calculated.
     * @return Transmittance from the point [from] to the point [to] in this media.
     */
    float GetTransmittance(const Point &from, const Point &to) const;

private:

    /** Shape that wraps the participate media.
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

#endif // RAY_TRACER_PARTICIPATIVEMEDIA_HPP
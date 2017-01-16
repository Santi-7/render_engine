/** ---------------------------------------------------------------------------
 ** simpleTexture.hpp
 ** Lambertian material based on an image. It repeats in the scene with the desired
 ** frequency using an arbitrary pixel size. Should only be used in planes!
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SIMPLETEXTURE_HPP
#define RAY_TRACER_SIMPLETEXTURE_HPP

#include <materials/material.hpp>
#include <image.hpp>

class SimpleTexture : public Material
{

public:

    /**
     * Loads the image filename
     *
     * @param filename Path to the texture image. Must be a .ppm image.
     * @return New Simple Texture material.
     */
    SimpleTexture(const string &filename, Dimension axis, float pixelSize = 0.0001f, Vect shift = Vect(0,0,0));

    /**
     * @return This material's color at the given point. Depends on the point's values relative to the world's axis
     *  and the texture loaded in this material.
     */
    Color GetDiffuse(const Point &point) const;

private:

    /** Texture. */
    Image mImage;

    /** Size of a pixel in the texture related to distance in the scene. */
    float mPixelSize;

    Vect mShift;
    /** Axis in which the plane containing this image lies. */
    Dimension mAxis;
};

#endif //RAY_TRACER_SIMPLETEXTURE_HPP

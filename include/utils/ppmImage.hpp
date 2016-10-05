/* ---------------------------------------------------------------------------
 ** ppmImage.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_PPMIMAGE_HPP
#define RAY_TRACER_PPMIMAGE_HPP

#include <array>
#include <color.hpp>
#include <string>

using namespace std;


    /**
     * Saves renderedImage as a ppm image file
     * @param renderedImage matrix with the rgb values of every pixel.
     * @param filename name of the saved file
     * @return
     */
    template<size_t rows, size_t cols>
    void SavePPMImage(array<array<Color, cols>, rows > &renderedImage, string filename);



#endif //RAY_TRACER_PPMIMAGE_HPP

/* ---------------------------------------------------------------------------
 ** ppmImage.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_PPMIMAGE_HPP
#define RAY_TRACER_PPMIMAGE_HPP

#include <vector>
#include <color.hpp>
#include <string>

using namespace std;

class PPMImage {

public:

    /**
     * This constructor saves renderedImage as a ppm image file
     * @param renderedImage matrix with the rgb values of every pixel.
     * @return
     */
    PPMImage(vector<vector<Color> > renderedImage, string filename);

};

#endif //RAY_TRACER_PPMIMAGE_HPP

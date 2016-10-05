/* ---------------------------------------------------------------------------
 ** image.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <vector>
#include <string>
#include <color.hpp>

using namespace std;

class Image {

public:
    Image(unsigned int width, unsigned int height);

    /**
     * Saves the image as a ppm file with the given filename
     * @param filename
     */
    void Save(string filename);

    /**
     * Overloads the subscript operator to read and write colors easily
     *
     * @param indexes tuple with the x, y coordinates of the pixel which color will be read/written
     * @return
     */
    vector<Color>& operator[](const unsigned int i);


private:
    vector<vector<Color> > mImage;

};


#endif //RAY_TRACER_IMAGE_HPP

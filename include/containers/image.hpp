/* ---------------------------------------------------------------------------
 ** image.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <color.hpp>
#include <string>
#include <vector>

using namespace std;

class Image {

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param width .
     * @param height .
     * @return .
     */
    Image(const unsigned int width, const unsigned int height);

    // TODO: Add doc.
    /**
     * Saves the image as a ppm file with the given filename.
     *
     * @param filename .
     */
    void Save(const string filename) const;

    // TODO: Add doc.
    /**
     * Overloads the subscript operator to read and write colors easily.
     *
     * @param i .
     * @return .
     */
    vector<Color> operator[](const unsigned int i) const;

private:

    vector<vector<Color>> mImage;
};

#endif // RAY_TRACER_IMAGE_HPP
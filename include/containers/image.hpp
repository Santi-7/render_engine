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

class Image
{

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


    /**
     * Parses a ppm image as an image
     * @param filename Path to the file containing a ppm image.
     */
    Image(const string & filename);

    // TODO: Add doc.
    /**
     * Saves the image as a ppm file with the given filename.
     *
     * @param filename .
     */
    void Save(const string filename) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    unsigned int GetWidth() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    unsigned int GetHeight() const;

    // TODO: Add doc.
    /**
     * Overloads the subscript operator to read and write colors easily.
     *
     * @param i .
     * @return .
     */
    vector<Color>& operator[](const unsigned int i);

private:

    // TODO: Add doc.
    /* . */
    vector<vector<Color>> mImage;
};

#endif // RAY_TRACER_IMAGE_HPP
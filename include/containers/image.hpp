/** ---------------------------------------------------------------------------
 ** image.hpp
 ** Container for an images grid of pixels. Each pixel is an RGB color. Contains
 ** an empty image constructor with width and height and a file input constructor.
 ** It can only load ppm image files.
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

enum SaveMode {DIM_TO_WHITE, GAMMA, CLAMP};

class Image
{

public:

    /**
     * @param width Desired width for this image.
     * @param height Desired height for this image.
     * @return New blank (black) Image with the desired with and height.
     */
    Image(const unsigned int width, const unsigned int height);

    /**
     * Loads a ppm image file as an image.
     *
     * @param filename Path to the file containing a ppm image.
     * @return New image containing the RGB values of the input file.
     */
    Image(const string & filename);

    /**
     * Saves this image as a ppm file with the given filename.
     *
     * @param filename Name for the file that will be created. Use with caution
     * since this won't check for the file's existance and will destroy it without
     * consideration.
     */
    void Save(const string filename, SaveMode mode = DIM_TO_WHITE) const;

    /**
     * @return This image's width.
     */
    unsigned int GetWidth() const;

    /**
     * @return This image's height.
     */
    unsigned int GetHeight() const;

    /**
     * Overloads the subscript operator to read and write colors easily.
     *
     * @param i Index of the line that will be returned.
     * @return i'th Line from the image matrix.
     */
    vector<Color>& operator[](const unsigned int i);

private:

    /** Pixel matrix. */
    vector<vector<Color>> mImage;
};

#endif // RAY_TRACER_IMAGE_HPP
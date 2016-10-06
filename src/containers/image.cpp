/* ---------------------------------------------------------------------------
 ** image.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <tuple>
#include <fstream>
#include "image.hpp"

Image::Image(const unsigned int width, const unsigned int height)
{
    // Resize the vector's height.
    mImage.resize(height);
    // Resize all rows to the desired width.
    for(unsigned int i = 0; i < height; ++i)
    {
        mImage.at(i).resize(width);
    }
}

void Image::Save(const string filename) const
{
    ofstream outputFile(filename);

    outputFile << "P3" << '\n' <<           // Write the header of the ppm file.
               "# " << filename << '\n' <<  // Write the name of the file as a comment.
               mImage[0].size() << ' ' << mImage.size() << '\n' <<
               255 << '\n';

    // Write the image's 2-dimensional array.
    for(unsigned int i = 0; i < mImage.size(); ++i)
    {
        for(unsigned int j = 0; j < mImage[0].size(); ++j)
        {
            outputFile << static_cast<int>(mImage[i][j].GetR()) << ' ' <<
                          static_cast<int>(mImage[i][j].GetG()) << ' ' <<
                          static_cast<int>(mImage[i][j].GetB()) << '\t';
        }
        outputFile << '\n';
    }
}

unsigned int Image::GetWidth() const
{
    return static_cast<int>(mImage[0].size());
}

unsigned int Image::GetHeight() const
{
    return static_cast<int>(mImage.size());
}

vector<Color> Image::operator[](const unsigned int i) const
{
    return mImage[i];
}
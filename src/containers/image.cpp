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

Image::Image(unsigned int width, unsigned int height)
{
    // Resize the vector's height
    mImage.resize(height);

    for(unsigned int i = 0; i < height; ++i)
    { // Resize all rows to the desired width
        mImage.at(i).resize(width);
    }
}

void Image::Save(string filename)
{
    ofstream outputFile(filename);

    outputFile << "P3" << '\n' << // Write the header of the ppm file
               "# " << filename << '\n' << // Write the name of the file as a comment
               mImage.at(0).size() << ' ' << mImage.size() << '\n' <<
               255 << '\n';

    // Write the image's 2-dimensional array
    for(unsigned int i = 0; i < mImage.size(); ++i)
    {
        for(unsigned int j = 0; j < mImage.at(0).size(); ++j)
        {
            outputFile << static_cast<int>(mImage.at(i).at(j).GetR()) << ' ' <<
                          static_cast<int>(mImage.at(i).at(j).GetG()) << ' ' <<
                          static_cast<int>(mImage.at(i).at(j).GetB()) << '\t';
        }
        outputFile << '\n';
    }
}

vector<Color>& Image::operator[](const unsigned int i)
{
    return mImage.at(i);
}

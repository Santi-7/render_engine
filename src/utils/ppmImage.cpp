/* ---------------------------------------------------------------------------
 ** ppmImage.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <fstream>
#include <ppmImage.hpp>

template<size_t rows, size_t cols>
void SavePPMImage(array<array<Color, cols>, rows > &renderedImage, string filename)
{
    ofstream outputFile(filename);

    outputFile << "P3" << '\n' << // Write the header of the ppm file
                  "# " << filename << '\n' << // Write the name of the file as a comment
                  renderedImage.at(0).size() << ' ' << renderedImage.size() << '\n' <<
                  255 << '\n';
    for(unsigned int i = 0; i < renderedImage.size(); ++i)
    {
        for(unsigned int j = 0; j < renderedImage.at(0).size(); ++j)
        {
            outputFile << renderedImage.at(i).at(j).GetR() << ' ' <<
                          renderedImage.at(i).at(j).GetR() << ' ' <<
                          renderedImage.at(i).at(j).GetR() << '\t';
        }
        outputFile << '\n';
    }
}
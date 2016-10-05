//
// Created by mjgal on 5/10/16.
//

#include "ppmImage.hpp"
#include <fstream>

PPMImage::PPMImage(vector<vector<Color> > &renderedImage, string filename)
{
    ofstream outputFile(filename);
    // TODO: Save the final image...
    outputFile << "P3" << '\n' << // Write the header of the ppm file
                  "# " << filename << '\n' << // Write the name of the file as a comment
                  renderedImage.at(0).size() << ' ' << renderedImage.size() << '\n' <<
                  255 << '\n';
    for(int i = 0; i < renderedImage.size(); ++i)
    {
        for(int j = 0; j < renderedImage.at(0).size(); ++j)
        {
            outputFile << renderedImage.at(i).at(j).GetR() << ' ' <<
                          renderedImage.at(i).at(j).GetR() << ' ' <<
                          renderedImage.at(i).at(j).GetR() << '\t';
        }
        outputFile << '\n';
    }
}
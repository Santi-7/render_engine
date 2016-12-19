/* ---------------------------------------------------------------------------
 ** image.cpp
 ** Implementation for Image class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <fstream>
#include <image.hpp>
#include <iostream>

Image::Image(const unsigned int width, const unsigned int height)
{
    // Resize the vector's height.
    mImage.resize(height);
    // Resize all rows to the desired width.
    for (unsigned int i = 0; i < height; ++i)
    {
        mImage.at(i).resize(width);
    }
}

Image::Image(const string &filename) {
    ifstream inputFile(filename);
    string buffer;

    if(!inputFile.good())
    {
        cout << "Can't read the file " << filename << '\n';
        throw 1;
    }

    while(true)
    {
        if (inputFile.peek() == '#')
        {
            // Ignore the line as a comment
            getline(inputFile, buffer);
            continue;
        }
        inputFile >> buffer;
        if (buffer == "P3") break;
        else
        {
            cout << "Can't find the ppm header for the file " << filename << '\n';
            throw 1;
        }
    }

    unsigned int width = 0, height = 0;
    while(true)
    {
        if (inputFile.peek() == '#' || inputFile.peek() == '\n')
        {
            // Ignore the line as a comment
            getline(inputFile, buffer);
            continue;
        }
        else
        {
            inputFile >> width >> height;
            break;
        }
    }

    if ((width == 0) | (height == 0))
    {
        cout << "Didn't find correct width and height in the input file " << filename << '\n';
        throw 1;
    }

    unsigned int maxColorValue = 0;
    while (true)
    {
        if ((inputFile.peek() == '#') | (inputFile.peek() == '\n'))
        {
            // Ignore the line as a comment
            getline(inputFile, buffer);
            continue;
        }
        else
        {
            inputFile >> maxColorValue;
            break;
        }
    }

    if (maxColorValue == 0)
    {
        cout << "Couldn't find maximum color value in " << filename << '\n';
        throw 1;
    }

    float r, g, b;

    // Resize mImage to account for all the values it'll hold
    mImage.resize(height);

    for ( unsigned int i = 0; i < height; ++i)
    {
        mImage[i].resize(width);
    }

    // Read all rgb values into the image vector. If this goes wrong use a correct image and it won't.
    for ( unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            inputFile >> r >> g >> b;
            r /= maxColorValue;
            g /= maxColorValue;
            b /= maxColorValue;

            mImage[i][j] = Color(r, g, b);
        }
    }
}

void Image::Save(const string filename, SaveMode mode) const
{
    ofstream outputFile(filename);

    outputFile << "P3" << '\n' <<          // Write the header of the ppm file.
               "# " << filename << '\n' << // Write the name of the file as a comment.
               mImage[0].size() << ' ' << mImage.size() << '\n' <<
               255 << '\n';

    // Find the largest single color value in the image to give it the value 255
    float largest = -1;
    for (unsigned int i = 0; i < mImage.size(); ++i)
    {
        for (unsigned int j = 0; j < mImage.at(i).size(); ++j)
        {
            if (mImage.at(i).at(j).GetR() > largest) largest = mImage.at(i).at(j).GetR();
            else if (mImage.at(i).at(j).GetG() > largest) largest = mImage.at(i).at(j).GetG();
            else if (mImage.at(i).at(j).GetB() > largest) largest = mImage.at(i).at(j).GetB();
        }
    }

    largest = largest < 1.0f ? 1.0f : largest;

    // Write the image's 2-dimensional array.
    for (unsigned int i = 0; i < mImage.size(); ++i)
    {
        for (unsigned int j = 0; j < mImage[0].size(); ++j)
        {
            Color tmp = mImage[i][j];

            switch(mode)
            {
            case DIM_TO_WHITE:
                tmp = tmp / largest;
                break;
            case GAMMA:
                tmp = tmp.GammaCorrect().Clamp();
                break;
            case CLAMP:
                tmp = tmp.Clamp();
                break;
            }
            outputFile << static_cast<unsigned int>(static_cast<unsigned char>(255 * tmp.GetR())) << ' ' <<
                          static_cast<unsigned int>(static_cast<unsigned char>(255 * tmp.GetG())) << ' ' <<
                          static_cast<unsigned int>(static_cast<unsigned char>(255 * tmp.GetB())) << '\t';
        }
        outputFile << '\n';
    }
    outputFile.close();
}

unsigned int Image::GetWidth() const
{
    return static_cast<int>(mImage[0].size());
}

unsigned int Image::GetHeight() const
{
    return static_cast<int>(mImage.size());
}

vector<Color>& Image::operator[](const unsigned int i)
{
    return mImage[i];
}
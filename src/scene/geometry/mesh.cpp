/* ---------------------------------------------------------------------------
** mesh.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <mesh.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

Mesh::Mesh(const string filename) : Shape(), mVertices(vector<Vertex>()), mFaces(vector<Face>())
{
    ifstream objFile(filename);
    string lineBuf;
    string lineType;
    istringstream lineStream;

    vector<Point> positions;
    vector<Vect> normals;

    float x, y, z;
    unsigned int a, b, c;

    while(objFile.good())
    {
        getline(objFile, lineBuf);
        if(lineBuf.size() == 0) continue;
        lineStream = istringstream(lineBuf);
        lineStream >> lineType;
        if(lineType == "v")
        {   // New vertex position
            lineStream >> x >> y >> z;
            positions.push_back(Point(x, y, z));
        }
        else if(lineType == "vn")
        {   // New vertex normal
            lineStream >> x >> y >> z;
            normals.push_back(Vect(x, y, z));
        }
        else if(lineType == "f")
        {   // New face
            lineStream >> a >> b >> c;
            mFaces.push_back(Face(a, b, c));
        }
        else continue;
    }

    if(positions.size() != normals.size())
    {
        cerr << "Error: the obj file doesn't define the same amount of vertices and normals\n";
        throw 1;
    }

    for(unsigned int i = 0; i < positions.size(); ++i)
    {
        mVertices.push_back(Vertex(positions.at(i), normals.at(i)));
    }
}

Mesh::Mesh(vector<Vertex> vertices, vector<Face> faces) : Shape(), mVertices(vertices), mFaces(faces){}

// Placehorder
float Mesh::Intersect(const LightRay &lightRay) const {return 0.0f;}

// Placehorder
Vect Mesh::GetNormal(const Point &point) const {return Vect(0,0,0);}
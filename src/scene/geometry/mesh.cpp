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
#include <cfloat>
#include <geometry/triangle.hpp>

using namespace std;

typedef tuple<unsigned int, unsigned int, unsigned int> Face;

vector<shared_ptr<Triangle>> ParseObjFile(const string filename)
{
    vector<shared_ptr<Triangle>> triangles;
    vector<Point> positions;
    vector<Vect> normals;
    vector<Face> faces;
    ifstream objFile(filename);
    string lineBuf;
    string lineType;
    istringstream lineStream;

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
            faces.push_back(Face(a-1, b-1, c-1));
        }
        else continue;
    }

    if(normals.size() == 0)
    {
        for (unsigned int i = 0; i < faces.size(); ++i) {
            Triangle tmp(positions.at(get<0>(faces.at(i))),
                        positions.at(get<1>(faces.at(i))),
                        positions.at(get<2>(faces.at(i))));

            triangles.push_back(make_shared<Triangle>(tmp));
        }
    }
    else {

        if (positions.size() != normals.size()) {
            cerr << "Error: the obj file doesn't define the same amount of vertices and normals\n";
            throw 1;
        }

        for (unsigned int i = 0; i < faces.size(); ++i) {
            triangles.push_back(
                    make_shared<MeshTriangle>(MeshTriangle(positions.at(get<0>(faces.at(i))),
                                                           positions.at(get<1>(faces.at(i))),
                                                           positions.at(get<2>(faces.at(i))),
                                                           normals.at(get<0>(faces.at(i))),
                                                           normals.at(get<1>(faces.at(i))),
                                                           normals.at(get<2>(faces.at(i))))));
        }
    }

    return triangles;
}

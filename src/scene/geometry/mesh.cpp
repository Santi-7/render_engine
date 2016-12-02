/* ---------------------------------------------------------------------------
** mesh.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <box.hpp>
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <mesh.hpp>
#include <sstream>

typedef std::tuple<unsigned int, unsigned int, unsigned int> Face;

void ClampPoints(vector<Point> &points, Point &maxValues, Point &minValues, float desiredMax, const Vect desiredCenter)
{
    Point meanValues((minValues.GetX() + maxValues.GetX()) / 2,
                     (minValues.GetY() + maxValues.GetY()) / 2,
                     (minValues.GetZ() + maxValues.GetZ()) / 2);

    // Get the maximum absolute value from all the values in the points. This way we can limit the maximum value to
    // be touching a face of a Cube in the origin between points -desiredMax and desiredMax
    float maxValue = max({maxValues.GetX() - meanValues.GetX(),
                          maxValues.GetY() - meanValues.GetY(),
                          maxValues.GetZ() - meanValues.GetZ()});
    float scaler = 1.0;
    float scaledMaxValue = maxValue / scaler;
    // Get a rough scale quickly
    while (scaledMaxValue > desiredMax)
    {
        scaler *= 2;
        scaledMaxValue = maxValue / scaler;
    }
    // If the greatest value is smaller than the desiredMax value we can't make it any smaller
    if (scaler == 1.0) return;
    // Dichotomic search for a more precise scaler.
    float leftScaler = scaler / 2;
    float rightScaler = scaler;
    scaler -= scaler / 4;
    while (abs(maxValue / scaler - desiredMax) > desiredMax/10000)
    {
        if (maxValue / scaler > desiredMax)
        {
            leftScaler= scaler;
        }
        else
        {
            rightScaler = scaler;
        }
        scaler = (leftScaler + rightScaler) / 2;
    }

    for (unsigned int i = 0; i < points.size(); ++i)
    {
        points[i] = Point((points[i].GetX() - meanValues.GetX()) / scaler,
                          (points[i].GetY() - meanValues.GetY()) / scaler,
                          (points[i].GetZ() - meanValues.GetZ()) / scaler) + desiredCenter;
    }

    // Work out the new centered maximum and minimum points in the origin of coordinates.
    maxValues = Point((maxValues.GetX() - meanValues.GetX()) / scaler,
                      (maxValues.GetY() - meanValues.GetY()) / scaler,
                      (maxValues.GetZ() - meanValues.GetZ()) / scaler) + desiredCenter;

    minValues = Point((minValues.GetX() - meanValues.GetX()) / scaler,
                      (minValues.GetY() - meanValues.GetY()) / scaler,
                      (minValues.GetZ() - meanValues.GetZ()) / scaler) + desiredCenter;

}

Mesh::Mesh(const string &filename, float maxDistFromOrigin, const Vect &shift)
{
    vector<Point> positions;
    vector<Vect> normals;
    vector<Face> faces;
    ifstream objFile(filename);
    string lineBuf;
    string lineType;
    istringstream lineStream;

    float x, y, z;
    unsigned int a, b, c;
    float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;
    while (objFile.good()) {
        getline(objFile, lineBuf);
        if (lineBuf.size() == 0) continue;
        lineStream = istringstream(lineBuf);
        lineStream >> lineType;
        if (lineType == "v")    // New vertex
        {
            lineStream >> x >> y >> z;
            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
            if (z < minZ) minZ = z;
            if (z > maxZ) maxZ = z;
            positions.push_back(Point(x, y, z));
        } else if (lineType == "vn") {   // New vertex normal
            lineStream >> x >> y >> z;
            normals.push_back(Vect(x, y, z));
        } else if (lineType == "f") {   // New face
            lineStream >> a >> b >> c;
            faces.push_back(Face(a - 1, b - 1, c - 1));
        } else continue;
    }

    Point maxValues(maxX, maxY, maxZ);
    Point minValues(minX, minY, minZ);

    if (maxDistFromOrigin != 0.0f)
    {
        ClampPoints(positions, maxValues, minValues, maxDistFromOrigin, shift);
    }

    if (normals.size() == 0)
    {
        for (unsigned int i = 0; i < faces.size(); ++i)
        {
            Triangle tmp(positions.at(get<0>(faces.at(i))),
                         positions.at(get<1>(faces.at(i))),
                         positions.at(get<2>(faces.at(i))));

            triangles.push_back(make_shared<Triangle>(tmp));
        }
    }
    else
    {

        if (positions.size() != normals.size())
        {
            cerr << "Error: the obj file doesn't define the same amount of vertices and normals\n";
            throw 1; // Stop execution
        }

        for (unsigned int i = 0; i < faces.size(); ++i)
        {
            triangles.push_back(
                    make_shared<MeshTriangle>(MeshTriangle(positions.at(get<0>(faces.at(i))),
                                                           positions.at(get<1>(faces.at(i))),
                                                           positions.at(get<2>(faces.at(i))),
                                                           normals.at(get<0>(faces.at(i))),
                                                           normals.at(get<1>(faces.at(i))),
                                                           normals.at(get<2>(faces.at(i))))));
        }
    }
    boundingShape = shared_ptr<Shape>(new Box(Rectangle(Vect(0,1,0), minValues, Point(maxValues.GetX(), minValues.GetY(), maxValues.GetZ())), maxValues.GetY() - minValues.GetY()));
    cout << maxValues << '\n';
    cout << minValues << '\n';
}

void Mesh::Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const
{
    if (boundingShape->Intersect(lightRay) != FLT_MAX)
    {
        for (unsigned int i = 0; i < triangles.size(); ++i)
        {
            triangles.at(i)->Intersect(lightRay, minT, nearestShape, triangles.at(i));
        }
    }
}

Vect Mesh::GetNormal(const Point &point) const
{
    throw 1;
}

float Mesh::Intersect(const LightRay &lightRay) const
{
    if (boundingShape->Intersect(lightRay) != FLT_MAX)
    {
        for (unsigned int i = 0; i < triangles.size(); ++i)
        {
            float tmp = triangles.at(i)->Intersect(lightRay);
            if (tmp != FLT_MAX) return tmp;
        }
    }
    return FLT_MAX;
}

void Mesh::SetMaterial(shared_ptr<Material> material)
{
    for (unsigned int i = 0; i < triangles.size(); ++i) {
        triangles.at(i)->SetMaterial(material);
    }
}
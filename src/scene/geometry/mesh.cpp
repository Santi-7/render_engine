/* ---------------------------------------------------------------------------
** mesh.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <box.hpp>
#include <cfloat>
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


Mesh Mesh::LoadObjFile(const string& filename, float maxDistFromOrigin, const Vect& shift, TransformationMatrix tm)
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
    float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;

    if (!objFile.good())
    {
        cout << "The file doesn't exist or can't be read for some reason.\n";
        throw 1;
    }

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
            positions.push_back(tm * Point(x, y, z));
        } else if (lineType == "vn") {   // New vertex normal
            lineStream >> x >> y >> z;
            normals.push_back(tm * Vect(x, y, z));
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
            Triangle tmp(positions.at(get<0>(faces[i])),
                    positions.at(get<1>(faces[i])),
                    positions.at(get<2>(faces[i])));

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
                    make_shared<MeshTriangle>(MeshTriangle(positions.at(get<0>(faces[i])),
                            positions.at(get<1>(faces[i])),
                            positions.at(get<2>(faces[i])),
                            normals.at(get<0>(faces[i])),
                            normals.at(get<1>(faces[i])),
                            normals.at(get<2>(faces[i])))));
        }
    }

    return Mesh(triangles);
}

Mesh::Mesh(vector<shared_ptr<Triangle>> triangles)
{
    float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;

    // Find the maximum and minimum values for the three coordinates.
    // This will let us create the bounding box and divide the triangles into two.
    for (const shared_ptr<Triangle> &t : triangles)
    {
        // Check Point A
        if (t->mA.GetX() < minX) minX = t->mA.GetX();
        if (t->mA.GetX() > maxX) maxX = t->mA.GetX();
        if (t->mA.GetY() < minY) minY = t->mA.GetY();
        if (t->mA.GetY() > maxY) maxY = t->mA.GetY();
        if (t->mA.GetZ() < minZ) minZ = t->mA.GetZ();
        if (t->mA.GetZ() > maxZ) maxZ = t->mA.GetZ();

        // Check Point B
        if (t->mB.GetX() < minX) minX = t->mB.GetX();
        if (t->mB.GetX() > maxX) maxX = t->mB.GetX();
        if (t->mB.GetY() < minY) minY = t->mB.GetY();
        if (t->mB.GetY() > maxY) maxY = t->mB.GetY();
        if (t->mB.GetZ() < minZ) minZ = t->mB.GetZ();
        if (t->mB.GetZ() > maxZ) maxZ = t->mB.GetZ();

        // Check Point C
        if (t->mC.GetX() < minX) minX = t->mC.GetX();
        if (t->mC.GetX() > maxX) maxX = t->mC.GetX();
        if (t->mC.GetY() < minY) minY = t->mC.GetY();
        if (t->mC.GetY() > maxY) maxY = t->mC.GetY();
        if (t->mC.GetZ() < minZ) minZ = t->mC.GetZ();
        if (t->mC.GetZ() > maxZ) maxZ = t->mC.GetZ();
    }

    // Get the bounding shape
    mBoundingShape = shared_ptr<Shape>(
            new Box(Rectangle(Vect(0, 1, 0), Point(minX, minY, minZ), Point(maxX, minY, maxZ)), maxY - minY));
    // If there are less than 32 triangles make this Mesh a leaf
    if (triangles.size() <= 32)
    {
        mIsLeaf = true;
        mTriangles = triangles;
    }
    else
    {
        // Find the axis with the greatest 'size'
        float xSize = maxX - minX;
        float ySize = maxY - minY;
        float zSize = maxZ - minZ;
        float maxSize = max({xSize, ySize, zSize});

        // Sort the triangle vector by the greatest axis
        if (maxSize == xSize)
        {
            sort(triangles.begin(), triangles.end(), [](shared_ptr<Triangle> &t1, shared_ptr<Triangle> &t2)
            {
                return t1->GetCenter().GetX() > t2->GetCenter().GetX();
            });
        }
        else if (maxSize == ySize)
        {
            sort(triangles.begin(), triangles.end(), [](shared_ptr<Triangle> &t1, shared_ptr<Triangle> &t2)
            {
                return t1->GetCenter().GetY() > t2->GetCenter().GetY();
            });

        }
        else
        {
            sort(triangles.begin(), triangles.end(), [](shared_ptr<Triangle> &t1, shared_ptr<Triangle> &t2)
            {
                return t1->GetCenter().GetZ() > t2->GetCenter().GetZ();
            });
        }


        // Split the triangle vector into two halves
        vector<shared_ptr<Triangle>> firstHalf(triangles.begin(), triangles.begin() + triangles.size()/2);
        vector<shared_ptr<Triangle>> secondHalf(triangles.begin() + triangles.size()/2, triangles.end());

        mLeft = make_shared<Mesh>(Mesh(firstHalf));
        mRight = make_shared<Mesh>(Mesh(secondHalf));
    }
}

Mesh::Mesh(const string &filename, float maxDistFromOrigin, const Vect &shift)
{
    mIsLeaf = true;
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
            Triangle tmp(positions.at(get<0>(faces[i])),
                         positions.at(get<1>(faces[i])),
                         positions.at(get<2>(faces[i])));

            mTriangles.push_back(make_shared<Triangle>(tmp));
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
            mTriangles.push_back(
                    make_shared<MeshTriangle>(MeshTriangle(positions.at(get<0>(faces[i])),
                                                           positions.at(get<1>(faces[i])),
                                                           positions.at(get<2>(faces[i])),
                                                           normals.at(get<0>(faces[i])),
                                                           normals.at(get<1>(faces[i])),
                                                           normals.at(get<2>(faces[i])))));
        }
    }
    mBoundingShape = shared_ptr<Shape>(new Box(Rectangle(Vect(0,1,0), minValues, Point(maxValues.GetX(), minValues.GetY(), maxValues.GetZ())), maxValues.GetY() - minValues.GetY()));
}

void Mesh::Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const
{
    if (mIsLeaf)
    {
        if (mBoundingShape->Intersect(lightRay) != FLT_MAX)
        {
            for (unsigned int i = 0; i < mTriangles.size(); ++i)
            {
                mTriangles[i]->Intersect(lightRay, minT, nearestShape, mTriangles[i]);
            }
        }
    }
    else
    {
        float boundT = IntersectBound(lightRay);
        if (boundT != FLT_MAX)
        {
            MeshIntersect(lightRay, minT, boundT, nearestShape);
        }
    }
}

float Mesh::Intersect(const LightRay &lightRay) const
{
    if (mIsLeaf)
    {
        if (mBoundingShape->Intersect(lightRay) != FLT_MAX)
        {
            for (unsigned int i = 0; i < mTriangles.size(); ++i)
            {
                float tmp = mTriangles[i]->Intersect(lightRay);
                if (tmp != FLT_MAX) return tmp;
            }
        }
        return FLT_MAX;
    }
    else if (IntersectBound(lightRay) != FLT_MAX)
    {
        float t = FLT_MAX;
        shared_ptr<Shape> stubPtr;
        MeshIntersect(lightRay, t, FLT_MAX, stubPtr);
        return t;
    }
    else
    {
        return FLT_MAX;
    }
}

void Mesh::MeshIntersect(const LightRay& lightRay, float& minT, float maxT, shared_ptr<Shape>& nearestShape) const
{
    if (mIsLeaf)
    {
        Intersect(lightRay, minT, nearestShape, nullptr);
        return;
    }
    // else
    float leftT = mLeft->IntersectBound(lightRay);
    float rightT = mRight->IntersectBound(lightRay);

    if ((rightT >= FLT_MAX) & (leftT >= FLT_MAX))
    {
        return;
    }

    if (leftT < rightT)
    {
        mLeft->MeshIntersect(lightRay, minT, FLT_MAX, nearestShape);

        if (rightT < minT)
        {
            mRight->MeshIntersect(lightRay, minT, minT, nearestShape);
        }
    }
    else
    {
        mRight->MeshIntersect(lightRay, minT, FLT_MAX, nearestShape);

        if (leftT < minT)
        {
            mLeft->MeshIntersect(lightRay, minT, minT, nearestShape);
        }
    }
}

float Mesh::IntersectBound(const LightRay& lightRay) const
{
    return mBoundingShape->Intersect(lightRay);
}

Vect Mesh::GetNormal(const Point &point) const
{
    throw 1;
}

void Mesh::SetMaterial(shared_ptr<Material> material)
{
    if (mIsLeaf)
    {
        for (unsigned int i = 0; i < mTriangles.size(); ++i) {
            mTriangles[i]->SetMaterial(material);
        }
    }
    else
    {
        mLeft->SetMaterial(material);
        mRight->SetMaterial(material);
    }

}


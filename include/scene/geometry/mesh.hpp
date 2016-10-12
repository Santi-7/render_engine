/* ---------------------------------------------------------------------------
** mesh.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MESH_HPP
#define RAY_TRACER_MESH_HPP

#include <shape.hpp>
#include <vector>
#include <vertex.hpp>
#include <tuple>

class Mesh : public Shape {

public:

    typedef tuple<unsigned int, unsigned int, unsigned int> Face;

    /**
     * Create a new Mesh from an obj (a simple one that defines vertices, vertex normals and faces)
     * @param filename must be a valid obj file path
     */
    Mesh(const string filename);

    /**
     * Create a new Mesh that contains the specified vertices and faces.
     * @param vertices all vertices conforming this mesh
     * @param faces indexes to the vertices that form triangles
     * @return
     */
    Mesh(vector<Vertex> vertices, vector<Face> faces);

    float Intersect(const LightRay &lightRay) const;

    Vect GetNormal(const Point &point) const;

private:

    vector<Vertex> mVertices;
    vector<Face> mFaces;
};

#endif //RAY_TRACER_MESH_HPP

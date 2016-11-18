/* ---------------------------------------------------------------------------
** mesh.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MESH_HPP
#define RAY_TRACER_MESH_HPP

#include <vector>
#include <memory>
#include <meshTriangle.hpp>

using namespace std;

class Mesh : public Shape {

public:
    /**
     * Constructs a new Mesh from an obj file.
     *   Keep in mind that this constructor only reads a subset of everything an obj file
     *   describes. It ignores materials and, some ways of defining faces. Texture mapping may
     *   be implemented in a later date. // TODO: Implement texture mapping
     *
     * @param filename Path to the obj file containing a mesh.
     * @return Mesh object.
     */
    Mesh(const string &filename);

    float Intersect(const LightRay &lightRay) const;

    /**
     * If the triangle that is closest to the lightRay origin (if any triangle intersects it) is
     * at a smaller distance from that point than t then:
     *  t is updated to that distance
     *  nearestShape is updated to the triangle closest to the lightray's origin.
     *
     * @param minT Distance from the lightray's origin to nearestShape.
     * @param nearestShape Shape that is at distance t from the lightray's origin.
     * @param lightRay The LightRay we are checking for intersections.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const;
    /**
     * This method is not usable for this shape.
     * If called, a static error should pop up.
     */
    Vect GetVisibleNormal(const Point &point, const LightRay &seenFrom) const;

private:
    vector<shared_ptr<Triangle>> triangles;

};

/**
 * Create a new Mesh from an obj (a simple one that defines vertices, vertex normals and faces)
 * @param filename must be a valid obj file path
 */
vector<shared_ptr<Triangle>> ParseObjFile(const string filename);

#endif //RAY_TRACER_MESH_HPP

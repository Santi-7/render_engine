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
friend class Triangle;

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
    Mesh(const string &filename, float maxDistFromOrigin, const Vect &shift);

    Mesh(vector<shared_ptr<Triangle>> triangles);

    static Mesh LoadObjFile(const string &filename, float maxDistFromOrigin, const Vect &shift);

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
    Vect GetNormal(const Point &point) const;

    void SetMaterial(shared_ptr<Material> material);

private:
    bool mIsLeaf;
    shared_ptr<Mesh> mLeft;
    shared_ptr<Mesh> mRight;
    shared_ptr<Shape> mBoundingShape;
    vector<shared_ptr<Triangle>> mTriangles;
};

#endif //RAY_TRACER_MESH_HPP

/** ---------------------------------------------------------------------------
 ** mesh.hpp
 ** Defines shape made out of many triangles. Contains a method for loading
 ** triangles and vertex normals from obj files. It's not a complete load though,
 ** it can't load texture coordinates and only works when there is a 1 to 1 match
 ** for vertices and vertex normals or there are no vertex normals.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MESH_HPP
#define RAY_TRACER_MESH_HPP

#include <memory>
#include <meshTriangle.hpp>
#include <transformationMatrix.hpp>
#include <vector>

using namespace std;

class Mesh : public Shape
{

friend class Triangle;

public:

    /**
     * Constructs a new Mesh from an obj file.
     *   Keep in mind that this constructor only reads a subset of everything an obj file
     *   describes. It ignores materials and, some ways of defining faces. Texture mapping may
     *   be implemented in a later date, probably not though.
     *
     * @param filename Path to the obj file containing a mesh.
     * @param maxDistFromOrigin Maximum distance allowed for any point in the obj file from the
     * relative origin of coordinates.
     * @param shift Vector by which the relative origin of coordinates for this mesh will be moved.
     * @return New Mesh object loaded from obj file. A Mesh constructed like this will have
     *  a single bounding volume.
     */
    Mesh(const string &filename, float maxDistFromOrigin, const Vect &shift);

    /**
     * Recursively builds a tree of mesh objects dividing the triangles into two vectors
     * and calling this constructor for each of this one's children. The triangles are divided
     * by axis with the longest difference and sorted by the triangles middle point.
     *
     * If triangles contains less than 32 triangles this Mesh will be a leaf, stopping the recursion.
     *
     * @param triangles vector containing the triangles to build this Mesh out of.
     */
    Mesh(vector<shared_ptr<Triangle>> triangles);

    /**
     * Creates a new Mesh with bounding box hierarchy in a binary tree.
     *
     * @param filename Path to the obj file containing a mesh.
     * @param maxDistFromOrigin Maximum distance allowed for any point in the obj file from the
     * relative origin of coordinates.
     * @param shift Vector by which the relative origin of coordinates for this mesh will be moved.
     * @return
     */
    static Mesh LoadObjFile(const string &filename, float maxDistFromOrigin, const Vect &shift,
                            TransformationMatrix tm = TransformationMatrix());

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to any of this shape triangles. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX. To save time, this method will check for
     * intersections with it's bounding volumes first and then look for children intersections.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * If the triangle that is closest to the lightRay origin (if any triangle is intersected) is
     * at a distance smaller than minT then:
     *  minT is updated to that distance
     *  nearestShape is updated to the triangle closest to the lightray's origin.
     *
     * @param minT Distance from the lightray's origin to nearestShape.
     * @param nearestShape Shape that is at distance t from the lightray's origin.
     * @param lightRay The LightRay we are checking for intersections.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                   shared_ptr<Shape> thisShape) const;

    /**
     * Special intersect function for searching the Mesh 'tree'.
     * @param lightRay Origin and direction to check for intersections with this Mesh.
     * @param minT Minimum distance so far to the lightray. Will be updated if this Mesh gets a intersection at a smaller distance.
     * @param maxT Maximum distance to consider checking a bounding volume (allows us to stop checking branches).
     * @param nearestShape Nearest shape intersected by the lightray so far. Updated together with minT.
     */
    void MeshIntersect(const LightRay &lightRay, float &minT, const float maxT,
                       shared_ptr<Shape> &nearestShape) const;

    /**
     * Returns the distance from the lightray's origin to the this mesh's bounding shape.
     * If the bounding shape is not intersected by the lightray it returns FLT_MAX.
     * @param lightRay
     * @return Distance from the lightray's origin to the this mesh's bounding shape.
     */
    float IntersectBound(const LightRay &lightRay) const;

    /**
     * This method is not usable for this shape. Calling it will result in an exception. This is because a Mesh's normal
     * is undefined, all intersections will actually happen with the triangles contained within.
     */
    Vect GetNormal(const Point &point) const;

    /**
     * Set the material in all the triangles in the mesh.
     * @param material Pointer to the material to set in all the triangles in this Mesh.
     */
    void SetMaterial(shared_ptr<Material> material);

private:

    /** True if this Mesh has no children Meshes. */
    bool mIsLeaf = false;

    /** Left child Mesh. */
    shared_ptr<Mesh> mLeft;
    /** Right child Mesh. */
    shared_ptr<Mesh> mRight;
    /** Shape enclosing all the triangles in this mesh. */
    shared_ptr<Shape> mBoundingShape;
    /** All the triangles in this Mesh IF it's a leaf. If it's not a leaf it just remains empty. */
    vector<shared_ptr<Triangle>> mTriangles;
};

#endif // RAY_TRACER_MESH_HPP
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
#include <triangle.hpp>

/**
 * Create a new Mesh from an obj (a simple one that defines vertices, vertex normals and faces)
 * @param filename must be a valid obj file path
 */
vector<Triangle> ParseObjFile(const string filename);

#endif //RAY_TRACER_MESH_HPP

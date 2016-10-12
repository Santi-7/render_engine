/* ---------------------------------------------------------------------------
** vertex.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_VERTEX_H_H
#define RAY_TRACER_VERTEX_H_H

#include "point.hpp"

class Vertex : public Point
{
public:

    /**
     * Creates a new Vertex.
     * @param position value for the new Vertex's position
     * @param normal value for the new Vertex's normal
     * @return Vertex
     */
    Vertex(const float x, const float y, const float z, const Vect normal);

    /**
     * Creates a new Vertex.
     * @param position value for the new Vertex's position
     * @param normal value for the new Vertex's normal
     * @return Vertex
     */
    Vertex(const Point position, const Vect normal);


    /**
     * Get the normal vector of this vertex
     * @return normal Vect
     */
    Vect GetNormal() const;

private:

    Vect mNormal;
};

#endif //RAY_TRACER_VERTEX_H_H

/* ---------------------------------------------------------------------------
** vertex.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <vertex.hpp>

Vertex::Vertex(const float x, const float y, const float z, const Vect normal) : Point(x, y, z), mNormal(normal) {}

Vertex::Vertex(const Point position, const Vect normal) : Point(position), mNormal(normal) {}

Vect Vertex::GetNormal() const
{
    return mNormal;
}
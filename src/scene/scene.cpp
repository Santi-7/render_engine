/* ---------------------------------------------------------------------------
** scene.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <scene.hpp>

void Scene::SetCamera(const Camera &c)
{
    mCamera = c;
}

void Scene::SetNumberOfShapes(const unsigned int number)
{
    mShapes.resize(number);
}

void Scene::AddShape(const Shape &s)
{
    // TODO: Add Shape s.
}
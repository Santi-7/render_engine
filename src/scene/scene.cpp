/* ---------------------------------------------------------------------------
** scene.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <scene.hpp>

void Scene::SetCamera(const Camera &camera)
{
    mCamera = camera;
}

void Scene::SetNumberOfLightSources(const unsigned int number)
{
    mLightSources.resize(number);
}

void Scene::AddLightSource(const LightSource &lightSource)
{
    // TODO: Add LightSource lightSource.
}

void Scene::SetNumberOfShapes(const unsigned int number)
{
    mShapes.resize(number);
}

void Scene::AddShape(const Shape &shape)
{
    // TODO: Add Shape shape.
}
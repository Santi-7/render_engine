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

void Scene::AddLightSource(const LightSource &lightSource)
{
    mLightSources.push_back(lightSource);
}

void Scene::AddShape(const Shape &shape)
{
    mShapes.push_back(shape);
}
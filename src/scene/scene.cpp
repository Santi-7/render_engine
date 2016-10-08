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

void Scene::Render() const
{
    // The current pixel. We begin with the first one (0,0).
    Point currentPixel = mCamera.GetFirstPixel();
    // The first pixel of the current row.
    Point currentRow = currentPixel;
    // For all the pixels, trace a ray of light.
    for (unsigned int i = 0; i < mCamera.GetHeight(); ++i)
    {
        for (unsigned int j = 0; j < mCamera.GetWidth(); ++j)
        {
            // Next pixel.
            currentPixel = currentPixel + mCamera.GetRight() * mCamera.GetPixelSize();
            // TODO: Trace the ray of light.
        }
        // Next row.
        currentRow = currentRow - mCamera.GetUp() * mCamera.GetPixelSize();
        currentPixel = currentRow;
    }
}
/* ---------------------------------------------------------------------------
** scene.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <image.hpp>
#include <scene.hpp>

void Scene::Render() const
{
    // The rendered image.
    Image rendered(mCamera->GetWidth(), mCamera->GetHeight());
    // The current pixel. We begin with the first one (0,0).
    Point currentPixel = mCamera->GetFirstPixel();
    // The first pixel of the current row.
    Point currentRow = currentPixel;
    // For all the pixels, trace a ray of light.
    for (unsigned int i = 0; i < mCamera->GetHeight(); ++i)
    {
        for (unsigned int j = 0; j < mCamera->GetWidth(); ++j)
        {
            // Next pixel.
            currentPixel = currentPixel + mCamera->GetRight() * mCamera->GetPixelSize();
            // Get the color for the current pixel.
            rendered[i][j] = GetPixelColor(currentPixel);
        }
        // Next row.
        currentRow = currentRow - mCamera->GetUp() * mCamera->GetPixelSize();
        currentPixel = currentRow;
    }
    rendered.Save("uglyDot.ppm");
}

// TODO: Temporal implementation.
Color Scene::GetPixelColor(const Point &pixel) const
{
    // Lightray from the focal point of the camera to the pixel.
    LightRay lightRay(mCamera->GetFocalPoint(), pixel);
    // Distance to the nearest shape.
    float tMin = FLT_MAX;
    //Shape nearestShape;
    for (unsigned int i = 0; i < mShapes.size(); i++) {
        float t = mShapes[i]->Intersect(lightRay);
        if (t < tMin)
        {
            tMin = t;
            //nearestShape = mShapes[i];
        }
    }
    return tMin == FLT_MAX ? Color::BLACK : Color::WHITE;
}
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
#include <iostream>


unique_ptr<Image> Scene::Render() const
{
    // The rendered image.
    unique_ptr<Image> rendered = make_unique<Image>
            (mCamera->GetWidth(), mCamera->GetHeight());
    // The current pixel. We begin with the first one (0,0).
    Point currentPixel = mCamera->GetFirstPixel();
    // The first pixel of the current row.
    Point currentRow = currentPixel;
    // Pixels' distance in the camera intrinsics right and up.
    Vect advanceX(mCamera->GetRight() * mCamera->GetPixelSize());
    Vect advanceY(mCamera->GetUp() * mCamera->GetPixelSize());
    // For all the pixels, trace a ray of light.
    for (unsigned int i = 0; i < mCamera->GetHeight(); ++i)
    {
        for (unsigned int j = 0; j < mCamera->GetWidth(); ++j)
        {

            // Next pixel.
            currentPixel += advanceX;
            // Get the color for the current pixel.
            (*rendered)[i][j] = GetPixelColor(currentPixel);
        }
        // Next row.
        currentRow -= advanceY;
        currentPixel = currentRow;
    }
    return rendered;
}

// TODO: Temporal implementation.
Color Scene::GetPixelColor(const Point &pixel) const
{
    // Ray of light from the focal point of the camera to the pixel.
    LightRay lightRay(mCamera->GetFocalPoint(), pixel);
    // Distance to the nearest shape.
    float tMin = FLT_MAX;
    // Nearest shape intersected with the ray of light.
    shared_ptr<Shape> nearestShape;
    /* Intersect with all the shapes in the
     * scene to know which one is the nearest. */
    for (unsigned int i = 0; i < mShapes.size(); ++i) {
        float t = mShapes[i]->Intersect(lightRay);
        if (t < tMin)
        {
            tMin = t;
            nearestShape = mShapes[i];
        }
    }
    // No shape has been found.
    if (tMin == FLT_MAX) return BLACK;

    // Assume the path to a light is clear.
    Color retVal = WHITE;
    // Intersection point with the nearest shape found.
    Point intersection(lightRay.GetPoint(tMin));
    // Direct light to all the light sources.

    for (unsigned int i = 0; i < mLightSources.size(); ++i)
    {
        /* All the point lights of the current light source. This is done
         * because the light source may not only be one point light. */
        vector<Point> lights = mLightSources[i]->GetLights();
        // Direct light to all the point lights of the current light source.
        for (unsigned int j = 0; j < lights.size(); ++j)
        {
            // The current point light is not hidden.
            if (!IsShaded(LightRay(intersection, lights[j]), lights[j]))
            {

                float multiplier = lightRay.GetDirection().DotProduct(nearestShape->GetNormal(intersection));
                if (multiplier < 0 ) multiplier = -multiplier;
                retVal *= multiplier;
            }
            // The point light is hidden.
            else
            {
                retVal = BLACK;
            }
        }
    }
    return retVal;
}

bool Scene::IsShaded(const LightRay &lightRay, const Point &light) const
{
    // Distance from the intersection point to the point light.
    float tLight = lightRay.GetSource().Distance(light);
    LightRay ray = LightRay(lightRay.GetSource(), light);
    // Check if the point light is hidden,
    for (unsigned int i = 0; i < mShapes.size(); ++i)
    {
        /* The point light is hidden, because there is
         * a shape that intersects the ray of light. */
        float tShape = mShapes[i]->Intersect(ray);
        if (tShape >= 0 & tShape < tLight)
        {
            //cout << tShape << " " << tLight << "\n";
            return true;
        }
    }
    // No shape has intersected the ray of light.
    return false;
}

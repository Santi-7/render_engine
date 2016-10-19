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
            (*rendered)[i][j] = GetLightRayColor(
                    LightRay(mCamera->GetFocalPoint(), currentPixel), REFLECT_STEPS);
        }
        // Next row.
        currentRow -= advanceY;
        currentPixel = currentRow;
    }
    return rendered;
}

// TODO: Temporal implementation.
Color Scene::GetLightRayColor(const LightRay &lightRay,
                              unsigned int reflectedSteps) const
{
    /* The number of reflection steps has been reached. Following with
     * the reflection will get more accurate rendered images, but
     * with much more computing cost. */
    if (reflectedSteps == 0) return BLACK;

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

    // Intersection point with the nearest shape found.
    Point intersection(lightRay.GetPoint(tMin));
    // Normal to the shape in the intersection point.
    Vect normal = nearestShape->GetNormal(intersection);
    // Ray of light reflected in the intersection point.
    Vect reflectedDir = lightRay.GetDirection() -
            normal * lightRay.GetDirection().DotProduct(normal) * 2;
    LightRay reflectedRay = LightRay(intersection, reflectedDir);
    // The reflected light comes with an angle.
    float multiplier = reflectedRay.GetDirection().DotProduct(normal);
    multiplier = multiplier > 0 ? multiplier : -multiplier;

    Color rayColor = DirectLight(intersection, normal, lightRay.GetDirection());
    if (nearestShape->GetMaterial().IsReflective())
        rayColor += GetLightRayColor(reflectedRay, --reflectedSteps) * multiplier;
    return rayColor;
}

Color Scene::DirectLight(const Point &point, Vect &normal, const Vect &seenFrom) const
{
    // Assume the path to light is blocked.
    Color retVal = BLACK;
    // Take the normal which looks at the visible semi-sphere.
    float cosine = normal.DotProduct(seenFrom);
    if ((cosine > 0) | (cosine == 0 &
                        signbit(normal.GetX()) == signbit(seenFrom.GetX()) &
                        signbit(normal.GetY()) == signbit(seenFrom.GetY()) &
                        signbit(normal.GetZ()) == signbit(seenFrom.GetZ())))
    {
        normal *= -1;
    }
    // Direct light to all the light sources.
    for (unsigned int i = 0; i < mLightSources.size(); ++i)
    {
        /* All the point lights of the current light source. This is done
         * because the light source may not only be one point light. */
        vector<Point> lights = mLightSources[i]->GetLights();
        // Direct light to all the point lights of the current light source.
        for (unsigned int j = 0; j < lights.size(); ++j)
        {
            // Ray of light from the point to the current light.
            LightRay lightRay = LightRay(point, lights[j]);
            // The current point light is not hidden.
            if (!InShadow(lightRay, lights[j]))
            {
                // Cosine of the ray of light with the correct normal.
                float multiplier = lightRay.GetDirection().DotProduct(normal);
                /* Add the radiance from the current light if it
                   illuminates the [point] from the visible semi-sphere. */
                retVal += mLightSources[i]->GetColor(point) * max(multiplier, 0.0f);
            }
        }
    }
    return retVal;
}

bool Scene::InShadow(const LightRay &lightRay, const Point &light) const
{
    // Distance from the intersection point to the point light.
    float tLight = lightRay.GetSource().Distance(light);
    // Check if the point light is hidden,
    for (unsigned int i = 0; i < mShapes.size(); ++i)
    {
        /* The point light is hidden, because there is
         * a shape that intersects the ray of light. */
        float tShape = mShapes[i]->Intersect(lightRay);
        // TODO: 0.015 is different from threshold since the error can get to be this big?
        if (tShape > 0.015 & tShape < tLight)
        {
            return true;
        }
    }
    // No shape has intersected the ray of light.
    return false;
}
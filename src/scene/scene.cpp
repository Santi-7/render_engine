/* ---------------------------------------------------------------------------
** scene.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <image.hpp>
#include <poseTransformationMatrix.hpp>
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
            (*rendered)[i][j] = GetLightRayColor(
                    LightRay(mCamera->GetFocalPoint(), currentPixel),
                    SPECULAR_STEPS, DIFFUSE_STEPS);
        }
        // Next row.
        currentRow -= advanceY;
        currentPixel = currentRow;
    }
    return rendered;
}

// TODO: Temporal implementation.
Color Scene::GetLightRayColor(const LightRay &lightRay,
                              const unsigned int specularSteps,
                              const unsigned int diffuseSteps) const
{
    /* The number of specular and indirect steps has been reached.
     * Following the light will get more accurate rendered
     * images, but with much more computing cost. */
    if (specularSteps == 0 & diffuseSteps == 0) return BLACK;

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
    Vect normal = nearestShape->GetVisibleNormal(intersection, lightRay);
    /* Transformation matrix from the local coordinates with [intersection] as the
     * reference point, and [normal] as the z axis, to global coordinates. */
    // TODO: FIX FIX FIX THIS.
    /*PoseTransformationMatrix fromLocalToGlobal =
            PoseTransformationMatrix::GetPoseTransformation(intersection, normal).Inverse();
    cout << normal << " " << fromLocalToGlobal * Vect(0,0,1) << endl;*/
    PoseTransformationMatrix fromGlobalToLocal =
            PoseTransformationMatrix::GetPoseTransformation(intersection, normal);
    cout << fromGlobalToLocal * normal << " " << endl;
    //if (normal.Abs() != 1) cout << normal.Abs() << endl;

    return DirectLight(intersection, normal, lightRay, *nearestShape) +
           SpecularLight(intersection, normal, lightRay,
                         *nearestShape, specularSteps, diffuseSteps) +
           IndirectLight(intersection, normal, specularSteps, diffuseSteps);
}

Color Scene::DirectLight(const Point &point, Vect &normal,
                         const LightRay &seenFrom, const Shape &shape) const
{
    // Assume the path to light is blocked.
    Color retVal = BLACK;
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
                // Cosine of the ray of light with the visible normal.
                float multiplier = lightRay.GetDirection().DotProduct(normal);
                /* Add the radiance from the current light if it
                   illuminates the [point] from the visible semi-sphere. */
                retVal += // Li.
                          mLightSources[i]->GetColor(point) *
                          // Phong BRDF. Wo = seenFrom * -1, Wi = lightRay.
                          shape.GetMaterial()->PhongBRDF(seenFrom.GetDirection() * -1,
                                                         lightRay.GetDirection()) *
                          // Cosine.
                          max(multiplier, 0.0f);
            }
        }
    }
    return retVal;
}

// TODO: Add refraction.
Color Scene::SpecularLight(const Point &point, const Vect &normal,
                           const LightRay &in, const Shape &shape,
                           const unsigned int specularSteps,
                           const unsigned int diffuseSteps) const
{
    if (specularSteps <= 0) return BLACK;

    // Ray of light reflected in the intersection point.
    Vect reflectedDir = in.GetDirection() - normal * in.GetDirection().DotProduct(normal) * 2;
    LightRay out = LightRay(point, reflectedDir);
    // Ray of light refracted in the intersection point.

    return GetLightRayColor(out, specularSteps-1, diffuseSteps-1) *
           shape.GetMaterial()->GetReflectance();
}

Color Scene::IndirectLight(const Point &point, const Vect &normal,
                           const unsigned int specularSteps,
                           const unsigned int diffuseSteps) const
{
    if (diffuseSteps <= 0) return BLACK;

    // TODO: Add implementation using Monte Carlo.
    return BLACK;
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
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
#include <random>
#include <scene.hpp>
#include <iostream>
#include <thread>

void printProgressBar(unsigned int pixel, unsigned int total)
{
    int percentCompleted = static_cast<int>((pixel / static_cast<float>(total)) * 100);
    cout << '[';
    for (int i = 0; i < round(percentCompleted / 1.5); ++i)
    {
        cout << '=';
    }
    for (int i = 0; i < static_cast<int>(100/1.5) - round(percentCompleted / 1.5); ++i)
    {
        cout << ' ';
    }
    cout << "] " <<  percentCompleted << "% \r" << std::flush;
}

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
        printProgressBar(i, mCamera->GetHeight());
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
    printProgressBar(1,1);

    return rendered;
}

unique_ptr<Image> Scene::RenderMultiThread(const unsigned int threadCount) const
{
    shared_ptr<Image> image(new Image(mCamera->GetWidth(), mCamera->GetHeight()));

    vector<shared_ptr<vector<unsigned int>>> linesPerThread(threadCount);

    // Initialize all line vectors.
    for (unsigned int i = 0; i < threadCount; ++i){
       linesPerThread[i] = make_shared<vector<unsigned int>>(0);
    }

    // Fill all line vectors.
    for (unsigned int i = 0; i < mCamera->GetHeight(); ++i)
    {
        linesPerThread[i % threadCount]->push_back(i);
    }

    // Start printing the progress bar at 0% completion
    printProgressBar(0, 1);
    vector<thread> threads(threadCount);
    // Initialize and start threads. Each thread will render the lines in their corresponding vector.
    for (unsigned int i = 0; i < threadCount; ++i)
    {
        // j == 0 because only the first thread will print the progress bar.
        threads[i] = thread(&Scene::RenderPixelRange, this, linesPerThread[i], image, i == 0);
    }

    // Wait for all threads to end rendering their lines.
    for (unsigned int i = 0; i < threadCount; ++i)
    {
        threads[i].join();
    }

    printProgressBar(1, 1);

    return make_unique<Image>(*image);
}

void Scene::RenderPixelRange(const shared_ptr<vector<unsigned int>> horizontalLines,
                             const shared_ptr<Image> image, const bool printProgress) const
{
    // The current pixel. We begin with the first one (0,0).
    const Point firstPixel = mCamera->GetFirstPixel();
    // Pixels' distance in the camera intrinsics right and up.
    Vect advanceX(mCamera->GetRight() * mCamera->GetPixelSize());
    Vect advanceY(mCamera->GetUp() * mCamera->GetPixelSize());
    // The first pixel of the current row.
    Point currentPixel;
    // For all the pixels, trace a ray of light.
    for (unsigned int i = 0; i < horizontalLines->size(); ++i)
    {
        currentPixel = firstPixel - advanceY * (*horizontalLines)[i];
        for (unsigned int j = 0; j < mCamera->GetWidth(); ++j)
        {
            if (i == 317 and j == 57)
            {
                cout << "HEFAKLSFJG";
            }
            // Next pixel.
            currentPixel += advanceX;
            // Get the color for the current pixel.
            (*image)[(*horizontalLines)[i]][j] = GetLightRayColor(
                    LightRay(mCamera->GetFocalPoint(), currentPixel),
                    SPECULAR_STEPS, DIFFUSE_STEPS);
        }
        if (printProgress) printProgressBar(i, static_cast<unsigned int>(horizontalLines->size()));
    }
}

Color Scene::GetLightRayColor(const LightRay &lightRay,
                              const int specularSteps,
                              const int diffuseSteps) const
{
    /* The number of specular and indirect steps has been reached.
     * Following the light will get more accurate rendered
     * images, but with much more computing cost. */
    if ((specularSteps == 0) & (diffuseSteps == 0)) return BLACK;

    // Distance to the nearest shape.
    float minT = FLT_MAX;
    // Nearest shape intersected with the ray of light.
    shared_ptr<Shape> nearestShape;

    /* Intersect with all the shapes in the
     * scene to know which one is the nearest. */
    for (unsigned int i = 0; i < mShapes.size(); ++i) {
        mShapes.at(i)->Intersect(lightRay, minT, nearestShape, mShapes.at(i));
    }

    // No shape has been found.
    if (minT == FLT_MAX) return BLACK;

    // Intersection point with the nearest shape found.
    Point intersection(lightRay.GetPoint(minT));
    // Normal to the shape in the intersection point.
    Vect normal = nearestShape->GetVisibleNormal(intersection, lightRay);

    Color emmitedFromShape = nearestShape->GetEmitedLight();

    return DirectLight(intersection, normal, lightRay, *nearestShape) +
           SpecularLight(intersection, normal, lightRay,
                         *nearestShape, specularSteps, diffuseSteps) +
           DiffuseLight(intersection, normal, lightRay,
                        *nearestShape, specularSteps, diffuseSteps) +
           emmitedFromShape;
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
                                                         lightRay.GetDirection(),
                                                         normal, point) *
                          // Cosine.
                          max(multiplier, 0.0f);
            }
        }
    }
    return retVal;
}

Color Scene::SpecularLight(const Point &point, const Vect &normal,
                           const LightRay &in, const Shape &shape,
                           const int specularSteps, const int diffuseSteps) const
{
    Color retVal = BLACK;

    if (specularSteps<=0) return retVal;

    // Ray of light reflected in the intersection point.
    // TODO: Change to global method.
    if (shape.GetMaterial()->GetReflectance() != BLACK)
    {
        Vect reflectedDir = in.GetDirection() - normal * in.GetDirection().DotProduct(normal) * 2;
        LightRay reflectedRay = LightRay(point, reflectedDir);
        retVal += GetLightRayColor(reflectedRay, specularSteps-1, diffuseSteps-1) *
                  shape.GetMaterial()->GetReflectance();
    }

    if (shape.GetMaterial()->GetTransmittance() != BLACK)
    {
        // Ray of light refracted in the intersection point.
        LightRay refractedRay = shape.Refract(in, point, normal);

        retVal += GetLightRayColor(refractedRay, specularSteps-1, diffuseSteps-1) *
                  shape.GetMaterial()->GetTransmittance();
    }

    return retVal;
}

inline static tuple<float, float> UniformCosineSampling()
{
    // Random generator.
    static random_device randDev;
    static mt19937 mt(randDev());
    static uniform_real_distribution<float> distribution(0, 1);
    // Inclination and azimuth angles.
    float inclination = acos(sqrt(1 - distribution(mt)));
    float azimuth = 2 * PI * distribution(mt);
    return make_tuple(inclination, azimuth);
}

Color Scene::DiffuseLight(const Point &point, const Vect &normal,
                          const LightRay &in, const Shape &shape,
                          const int specularSteps, const int diffuseSteps) const
{
    if ((diffuseSteps <= 0) | ((shape.GetMaterial()->GetDiffuse(point) == BLACK) &
                               (shape.GetMaterial()->GetSpecular() == BLACK)))
        return BLACK;

    /* Transformation matrix from the local coordinates with [point] as the
     * reference point, and [normal] as the z axis, to global coordinates. */
    PoseTransformationMatrix fromLocalToGlobal =
            PoseTransformationMatrix::GetPoseTransformation(point, normal);
    // [DIFFUSE_RAYS] indirect rays of light using Monte Carlo sampling.
    Color retVal = BLACK;
    for (unsigned int i = 0; i < DIFFUSE_RAYS; i++)
    {
        // Generate random angles.
        float inclination, azimuth;
        tie(inclination, azimuth) = UniformCosineSampling();
        // Direction of the ray of light expressed in local coordinates.
        Vect localRay(sin(inclination) * cos(azimuth),
                      sin(inclination) * sin(azimuth),
                      cos(inclination));
        // Transform the ray of light to global coordinates.
        LightRay lightRay(point, fromLocalToGlobal * localRay);
        retVal += // Li.
                  GetLightRayColor(lightRay, specularSteps-1, diffuseSteps-1) *
                  // Phong BRDF. Wo = in * -1, Wi = lightRay.
                  shape.GetMaterial()->PhongBRDF(in.GetDirection() * -1,
                                                 lightRay.GetDirection(),
                                                 normal, point) *
                  // Cosine and sine. We can avoid it and not divide again later.
                  /* cos(inclination) * sin(inclination) */
                  // 1 / PDF.
                  (PI /* / (sin(inclination) * cos(inclination)) */ );
    }
    return retVal * shape.GetMaterial()->GetDiffuse(point)/ DIFFUSE_RAYS;
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
        if ((tShape > 0.015) & (tShape < tLight))
        {
            return true;
        }
    }
    // No shape has intersected the ray of light.
    return false;
}
/* ---------------------------------------------------------------------------
** scene.cpp
** Implementation for Scene class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cfloat>
#include <image.hpp>
#include <iostream>
#include <poseTransformationMatrix.hpp>
#include <scene.hpp>
#include <sphere.hpp>
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
                    LightRay(mCamera->GetFocalPoint(), currentPixel), mSpecularSteps);
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
            // Next pixel.
            currentPixel += advanceX;
            // Get the color for the current pixel.
            (*image)[(*horizontalLines)[i]][j] = GetLightRayColor(
                    LightRay(mCamera->GetFocalPoint(), currentPixel), mSpecularSteps);
        }
        if (printProgress) printProgressBar(i, static_cast<unsigned int>(horizontalLines->size()));
    }
}

void Scene::EmitPhotons()
{
    // Emit photons from each light source.
    for (shared_ptr<LightSource> light : mLightSources)
    {
        for (Point pointLight : light->GetLights())
        {
            /* Transformation matrix from the local coordinates with [point] as the
             * reference point, and [0,0,1] as the z axis, to global coordinates. */
            PoseTransformationMatrix fromLocalToGlobal =
                    PoseTransformationMatrix::GetPoseTransformation(pointLight, Vect(0,0,1));
            // [mPhotonsEmitted] photons uniformly emitted.
            for (unsigned int i = 0; i < mPhotonsEmitted / light->GetLights().size() / mLightSources.size(); i++)
            {
                // Generate random angles.
                float inclination, azimuth;
                tie(inclination, azimuth) = UniformSphereSampling();
                // Direction of the ray of light expressed in local coordinates.
                Vect localRay(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));
                // Transform the ray of light to global coordinates.
                ColoredLightRay lightRay(pointLight, fromLocalToGlobal * localRay,
                                         light->GetBaseColor() / mPhotonsEmitted / light->GetLights().size());
                /* The photons directly emitted from the light sources (direct light)
                 * are not saved in the photon map. */
                PhotonInteraction(lightRay, false, false);
            }
        }
    }
    mDiffusePhotonMap.Balance();
    mCausticsPhotonMap.Balance();
    for (tuple<shared_ptr<ParticipatingMedia>, KDTree> &mediaKDTree : mMediaPhotonMaps)
    {
        get<1>(mediaKDTree).Balance();
    }
}

void Scene::PhotonInteraction(const ColoredLightRay &lightRay, const bool save, bool fromCausticShape)
{
    // Distance to the nearest shape and the nearest media.
    float minT_Shape = FLT_MAX, minT_Media = FLT_MAX;
    // Nearest shape and media intersected with the ray of light.
    shared_ptr<Shape> nearestShape = nullptr;
    shared_ptr<ParticipatingMedia> nearestMedia = nullptr;

    /* Intersect with all the shapes in the
     * scene to know which one is the nearest. */
    for (unsigned int i = 0; i < mShapes.size(); ++i)
        mShapes.at(i)->Intersect(lightRay, minT_Shape, nearestShape, mShapes.at(i));

    /* Intersect with all the medias in the
     * scene to know which one is the nearest. */
    for (unsigned int i = 0; i < mMedia.size(); ++i)
    {
        float previousMinT = minT_Media;
        mMedia.at(i)->Intersect(lightRay, minT_Media);
        if (minT_Media < previousMinT) nearestMedia = mMedia.at(i);
    }

    // No shape and no media have been found.
    if ((minT_Shape == FLT_MAX) & (minT_Media == FLT_MAX)) return;

    // Is the ray of light inside the media?
    bool isInside = false;
    float nextInteraction = minT_Media;
    // There is at least one participating media.
    if (nearestMedia != nullptr)
    {
        isInside = nearestMedia->IsInside(lightRay.GetSource());
        // Next mean-free path
        if (isInside) nextInteraction = nearestMedia->GetNextInteraction();
        // Next mean-fre path after going into the media.
        else nextInteraction += nearestMedia->GetNextInteraction();
    }

    // The shape is closer than the media, intersect directly with the shape.
    if (minT_Shape <= minT_Media)
    {
        GeometryInteraction(lightRay, nearestShape, lightRay.GetPoint(minT_Shape), save, fromCausticShape);
    }
    // The media is closer than the shape.
    else  // minT_Shape > minT_Media
    {
        // We are exiting the media.
        if (isInside & (nextInteraction > minT_Media))
        {
            ColoredLightRay out(lightRay.GetPoint(minT_Media), lightRay.GetDirection(), lightRay.GetColor());
            PhotonInteraction(out, save, fromCausticShape);
        }
        // We remain in the media.
        else
        {
            MediaInteraction(lightRay, nearestMedia, lightRay.GetPoint(nextInteraction));
        }
    }
}

void Scene::GeometryInteraction(const ColoredLightRay &lightRay, const shared_ptr<Shape> &shape,
                                const Point &intersection, bool save, bool fromCausticShape)
{
    // Save if the shape's material does not lead to caustics and its diffuse component is BLACK
    auto material = shape->GetMaterial();
    save &= !((material->GetDiffuse(intersection) == BLACK) & ((material->GetSpecular() != BLACK) |
                                                               (material->GetTransmittance() != BLACK)));
    if (save)
    {
        if (fromCausticShape)
            mCausticsPhotonMap.Store(intersection, Photon(lightRay));
        else
            mDiffusePhotonMap.Store(intersection, Photon(lightRay));
    }

    // Russian Roulette: follow the photon trajectory if it's still living.
    bool fromCaustic;
    ColoredLightRay bouncedRay;
    bool isAlive = shape->RussianRoulette(lightRay, intersection, bouncedRay, fromCaustic);
    if (isAlive) PhotonInteraction(bouncedRay, true, fromCausticShape | fromCaustic);
}

void Scene::MediaInteraction(const ColoredLightRay &lightRay, const shared_ptr<ParticipatingMedia> &media,
                             const Point &interaction)
{
    for (tuple<shared_ptr<ParticipatingMedia>, KDTree> &mediaKDTree : mMediaPhotonMaps)
    {
        if (get<0>(mediaKDTree) == media)
        {
            get<1>(mediaKDTree).Store(interaction, Photon(lightRay));
            break;
        }
    }

    // Russian Roulette: follow the photon trajectory if it's still living.
    ColoredLightRay bouncedRay;
    bool isAlive = media->RussianRoulette(lightRay, interaction, bouncedRay);
    if (isAlive) PhotonInteraction(bouncedRay, true, false);
}

Color Scene::GetLightRayColor(const LightRay &lightRay, const int specularSteps) const
{
    /* The number of specular and indirect steps has been reached.
     * Following the light will get more accurate rendered
     * images, but with much more computing cost. */
    if (specularSteps == 0) return BLACK;

    // Distance to the nearest shape.
    float minT = FLT_MAX;
    // Nearest shape intersected with the ray of light.
    shared_ptr<Shape> nearestShape;

    /* Intersect with all the shapes in the
     * scene to know which one is the nearest. */
    for (unsigned int i = 0; i < mShapes.size(); ++i)
        mShapes.at(i)->Intersect(lightRay, minT, nearestShape, mShapes.at(i));

    // No shape has been found.
    if (minT == FLT_MAX) return MediaEstimateRadiance(lightRay);

    // Intersection point with the nearest shape found.
    Point intersection(lightRay.GetPoint(minT));
    // Normal to the shape in the intersection point.
    Vect normal = nearestShape->GetVisibleNormal(intersection, lightRay);

    Color emittedLight = nearestShape->GetEmittedLight();

    // Light is additive.
    return (DirectLight(intersection, normal, lightRay, *nearestShape) +
            SpecularLight(intersection, normal, lightRay, *nearestShape, specularSteps) +
            GeometryEstimateRadiance(intersection, normal, lightRay, *nearestShape) +
            emittedLight) * PathTransmittance(lightRay, minT) +
           MediaEstimateRadiance(minT, intersection, lightRay);
}

Color Scene::DirectLight(const Point &point, const Vect &normal,
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
                if (multiplier > 0.0f)
                {
                    retVal += // Li.
                              mLightSources[i]->GetColor(point) *
                              // Phong BRDF. Wo = seenFrom * -1, Wi = lightRay.
                              shape.GetMaterial()->PhongBRDF(seenFrom.GetDirection() * -1,
                                                             lightRay.GetDirection(),
                                                             normal, point) *
                              // Cosine.
                              multiplier *
                              // Transmittance along all the path.
                              PathTransmittance(LightRay(point, lights[j]), point.Distance(lights[j]));
                }
            }
        }
    }
    return retVal;
}

Color Scene::SpecularLight(const Point &point, const Vect &normal,
                           const LightRay &in, const Shape &shape,
                           const int specularSteps) const
{
    Color retVal = BLACK;

    if (specularSteps<=0) return retVal;

    if (shape.GetMaterial()->GetReflectance() != BLACK)
    {
        // Ray of light reflected in the intersection point.
        Vect reflectedDir = Shape::Reflect(in.GetDirection(), normal);
        LightRay reflectedRay = LightRay(point, reflectedDir);

        retVal += GetLightRayColor(reflectedRay, specularSteps-1) *
                  shape.GetMaterial()->GetReflectance();
    }

    if (shape.GetMaterial()->GetTransmittance() != BLACK)
    {
        // Ray of light refracted in the intersection point.
        LightRay refractedRay = shape.Refract(in, point, normal);

        retVal += GetLightRayColor(refractedRay, specularSteps-1) *
                  shape.GetMaterial()->GetTransmittance();
    }

    return retVal;
}

Color Scene::GeometryEstimateRadiance(const Point &point, const Vect &normal,
                                      const LightRay &in, const Shape &shape) const
{
    if ((shape.GetMaterial()->GetDiffuse(point) == BLACK) &
        (shape.GetMaterial()->GetSpecular() == BLACK))
        return BLACK;

    Color retVal = BLACK;

    vector<const Node *> nodeList;
    float radius;
    mDiffusePhotonMap.Find(point, mPhotonsNeighbours, nodeList, radius);

    // Add the radiance of all the nearest photons calculated.
    for (auto nodeIt = nodeList.begin(); nodeIt < nodeList.end(); ++nodeIt)
    {
        Photon tmpPhoton = (*nodeIt)->GetData();
        // Cosine of the photon's direction with the visible normal.
        float multiplier = tmpPhoton.GetVect().DotProduct(normal);
        /* Add the radiance of the current photon if it
           illuminates the [point] from the visible semi-sphere. */
        if (multiplier < 0.0f)
        {
            retVal += // Li.
                      tmpPhoton.GetFlux() *
                      // Phong BRDF. Wo = in * -1, Wi = tmpPhoton.
                      shape.GetMaterial()->PhongBRDF(in.GetDirection() * -1,
                                                     tmpPhoton.GetVect(),
                                                     normal, point) *
                      // Gaussian kernel.
                      GaussianKernel(point, (*nodeIt)->GetPoint(), radius);
        }
    }

    // Estimate radiance for caustics
    float causticRadius;
    mCausticsPhotonMap.Find(point, mPhotonsNeighbours, nodeList, causticRadius);

    Color causticRetVal = BLACK;
    // Add the radiance of all the nearest photons calculated.
    for (auto nodeIt = nodeList.begin(); nodeIt < nodeList.end(); ++nodeIt)
    {
        Photon tmpPhoton = (*nodeIt)->GetData();
        // Cosine of the photon's direction with the visible normal.
        float multiplier = tmpPhoton.GetVect().DotProduct(normal);
        /* Add the radiance of the current photon if it
           illuminates the [point] from the visible semi-sphere. */
        if (multiplier < 0.0f)
        {
            causticRetVal += // Li.
                             tmpPhoton.GetFlux() *
                             // Phong BRDF. Wo = in * -1, Wi = tmpPhoton.
                             shape.GetMaterial()->PhongBRDF(in.GetDirection() * -1,
                                                            tmpPhoton.GetVect(),
                                                            normal, point) *
                             // Gaussian kernel.
                             GaussianKernel(point, (*nodeIt)->GetPoint(), causticRadius);
        }
    }

    // Divide the radiance between the sphere volume that wraps the nearest photons.
    return retVal / Sphere::Volume(radius) + causticRetVal / Sphere::Volume(causticRadius);
}

Color Scene::MediaEstimateRadiance(const float tIntersection, const Point &intersection, const LightRay &in) const
{
    Color retVal = BLACK;
    unsigned int insidePhotons = 0;

    /* Check which media does the LightRay intersect, so that we only estimate
     * those photons of the intersected media. */
    for (auto media : mMedia)
    {
        float tMedia = FLT_MAX;
        media->Intersect(in, tMedia);
        // The media es behind the intersection with the nearest shape at [tIntersection].
        if (tMedia > tIntersection) continue;

        Color mediaColor = BLACK;
        for (const tuple<shared_ptr<ParticipatingMedia>, KDTree> &mediaKDTree : mMediaPhotonMaps)
        {
            if (get<0>(mediaKDTree) == media)
            {
                // Get all photons of this media. Photon 0 is not useful.
                for (unsigned int i = 1; i < get<1>(mediaKDTree).Size(); ++i)
                {
                    Node photon = get<1>(mediaKDTree)[i];
                    // Distances from the photon to the ray of light.
                    float distance, tProjection;
                    tie(distance, tProjection) = in.Distance(photon.GetPoint());
                    // This photon is outside the beam.
                    if (distance > mBeamRadius) continue;
                    // This photon is behind the intersection with the nearest shape at [tIntersection].
                    if (tProjection > tIntersection) continue;
                    /* Add this photon contribution. */
                    insidePhotons++;
                    // Transmittance from this photon projection onto the RayLight, to the intersection.
                    LightRay fromPhoton(in.GetPoint(tProjection), in.GetDirection());
                    float distanceTransmittance = PathTransmittance(fromPhoton, tIntersection);
                    // Photon contribution.
                    mediaColor += // Flux.
                                  photon.GetData().GetFlux() *
                                  // Kernel.
                                  SilverManKernel(distance / mBeamRadius) / (mBeamRadius*mBeamRadius) *
                                  // Transmittance.
                                  media->GetTransmittance(distanceTransmittance);
                }
            }
        }
        // Homogeneous and isotropic media.
        retVal += mediaColor * media->GetScattering() * ParticipatingMedia::PHASE_FUNCTION;
    }

    return insidePhotons == 0 ? retVal : (retVal / insidePhotons);
}

Color Scene::MediaEstimateRadiance(const LightRay &in) const
{
    Color retVal = BLACK;
    unsigned int insidePhotons = 0;

    /* Check which media does the LightRay intersect, so that we only estimate
     * those photons of the intersected media. */
    for (auto media : mMedia)
    {
        float tMedia;
        media->Intersect(in, tMedia);
        // The LightRay doesn't intersect the media.
        if (tMedia == FLT_MAX) continue;

        Color mediaColor = BLACK;
        for (const tuple<shared_ptr<ParticipatingMedia>, KDTree> &mediaKDTree : mMediaPhotonMaps)
        {
            if (get<0>(mediaKDTree) == media)
            {
                // Get all photons of this media. Photon 0 is not useful.
                for (unsigned int i = 1; i < get<1>(mediaKDTree).Size(); ++i)
                {
                    Node photon = get<1>(mediaKDTree)[i];
                    // Distances from the photon to the ray of light.
                    float distance, tProjection;
                    tie(distance, tProjection) = in.Distance(photon.GetPoint());
                    // This photon is outside the beam.
                    if (distance > mBeamRadius) continue;
                    /* Add this photon contribution. */
                    insidePhotons++;
                    // Distance from this photon to the end of the media (direction of the LightRay).
                    LightRay fromPhoton(in.GetPoint(tProjection), in.GetDirection());
                    float distanceTransmittance = PathTransmittance(fromPhoton, FLT_MAX);
                    // Photon contribution.
                    mediaColor += // Flux.
                                  photon.GetData().GetFlux() *
                                  // Kernel.
                                  SilverManKernel(distance / mBeamRadius) / (mBeamRadius*mBeamRadius) *
                                  // Transmittance.
                                  media->GetTransmittance(distanceTransmittance);
                }
            }
        }

        // Homogeneous and isotropic media.
        retVal += mediaColor * media->GetScattering() * ParticipatingMedia::PHASE_FUNCTION;
    }

    return insidePhotons == 0 ? retVal : (retVal / insidePhotons);
}

// Alpha and beta values taken from https://graphics.stanford.edu/courses/cs348b-00/course8.pdf
float Scene::GaussianKernel(const Point &point, const Point &photon, const float radius)
{
    constexpr static float ALPHA = 0.918f, BETA = 1.953f;
    float distance = point.Distance(photon);
    return ALPHA * (1 - ((1 - exp(-BETA * (distance*distance / 2*radius*radius))) / (1 - exp(-BETA))));
}

float Scene::SilverManKernel(const float x)
{
    return 3 / PI * pow(1 - x*x, 2);
}

float Scene::PathTransmittance(const LightRay &lightRay, float tIntersection) const
{
    float totalTransmittance = 1;
    float tCurrent = 0;
    LightRay in = lightRay;

    // Calculate the transmittance in all the path until tIntersection.
    while (tIntersection > 0)
    {
        in = LightRay(in.GetPoint(tCurrent), in.GetDirection());

        // Distance to the nearest media.
        float minT_Media = FLT_MAX;
        // Nearest media intersected with the ray of light.
        shared_ptr<ParticipatingMedia> nearestMedia = nullptr;

        /* Intersect with all the medias in the
         * scene to know which one is the nearest. */
        for (unsigned int i = 0; i < mMedia.size(); ++i)
        {
            float previousMinT = minT_Media;
            mMedia.at(i)->Intersect(in, minT_Media);
            if (minT_Media < previousMinT) nearestMedia = mMedia.at(i);
        }

        // We are inside the nearest media (if exists).
        // Threshold to get we are inside the media when we are exactly in the media's boundary.
        if ((nearestMedia != nullptr) && nearestMedia->IsInside(lightRay.GetPoint(tCurrent + Point::TH)))
        {
            tCurrent = min(tIntersection, minT_Media);
            totalTransmittance *= nearestMedia->GetTransmittance(tCurrent);
        }
        // We are outside the nearest media, or it doesn't exist.
        else tCurrent = minT_Media;

        tIntersection -= tCurrent;
    }

    return totalTransmittance;
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
        if (tShape < tLight) return true;
    }
    // No shape has intersected the ray of light.
    return false;
}

/** ---------------------------------------------------------------------------
 ** scene.hpp
 ** Contains everything we need to render an Image, that is:
 **    Camera,
 **    Lights,
 **    List of shapes
 **    Rendering methods.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include <camera.hpp>
#include <coloredLightRay.hpp>
#include <kdtree.hpp>
#include <lightSource.hpp>
#include <memory>
#include <participatingMedia.hpp>
#include <shape.hpp>
#include <vector>

using namespace std;

class Scene
{

public:

    /**
     * Sets a camera for this scene.
     *
     * @tparam C Class of the camera.
     * @param camera Camera for this scene.
     */
    template <class C>
    void SetCamera(const C &camera)
    {
        mCamera = make_unique<C>(camera);
    }

    /**
     * Adds a lightSource to this scene.
     *
     * @tparam LS Class of the light source.
     * @param lightSource LightSource to add to the scene.
     */
    template <class LS>
    void AddLightSource(const LS &lightSource)
    {
        mLightSources.push_back(make_shared<LS>(lightSource));
    }

    /**
     * Adds a shape to this scene.
     *
     * @tparam S Class of the shape.
     * @param shape Shape to add to the scene.
     */
    template <class S>
    void AddShape(const S &shape)
    {
        mShapes.push_back(make_shared<S>(shape));
    }

    /**
     * Adds a participating media to this scene.
     *
     * @tparam PM Class of the Participating Media.
     * @param participatingMedia Participating media to add to the scene.
     */
    template <class PM>
    void AddParticipatingMedia(const PM &participatingMedia)
    {
        mMedia.push_back(make_shared<PM>(participatingMedia));
    }

    /**
     * Sets this Scene's image width and height.
     *
     * @param width Width pixels dimension of the virtual image.
     * @param height Height pixels dimension of the virtual image.
     */
    void SetImageDimensions(unsigned int width, unsigned int height)
    {
        mCamera->SetImageDimensions(width, height);
    }

    /**
     * Sets the number of specular steps to take when rendering the image.
     *
     * @param steps Number of specular steps.
     */
    void SetSpecularSteps(unsigned int steps)
    {
        mSpecularSteps = steps;
    }

    /**
     * Sets the number of photons to emit from every light source.
     *
     * @param photonCount Number of emitted photons.
     */
    void SetEmitedPhotons(unsigned int photonCount)
    {
        mPhotonsEmitted = photonCount;
    }

    /**
     * Sets the number of photons to search in each intersection in the final ray tracing step.
     *
     * @param kNeighbours Number of searched photons in the estimation phase.
     */
    void SetKNearestNeighbours(unsigned int kNeighbours)
    {
        mPhotonsNeighbours = kNeighbours;
    }

    /**
     * The main ray tracing algorithm. Traces lightRays from the camera to all the pixels in the image plane, calculates
     * intersections (and all their complicated interactions), and saves the color of each pixel in an image object.
     * Since this takes a while, it prints a beautiful progress bar indicating the percent of lines completed.
     *
     * @return Pointer to the rendered Image.
     */
    unique_ptr<Image> Render() const;

    /**
     * Divides the image into non contiguous lists of lines giving each list to a thread to render them separately.
     *
     * @param threads Number of threads that will render the image.
     * @return Pointer to the rendered Image.
     */
    unique_ptr<Image> RenderMultiThread(const unsigned int threads) const;

    /**
     * Emits all the photons defined for all LightSources in this scene. After their first bounce, all photons will be
     * stored in the internal KDTrees to later be accessed by the render method.
     */
    void EmitPhotons();

private:

    /** Limit to the specular interactions allowed. */
    unsigned int mSpecularSteps = 4;

    /** Number of individual photons that will be emitted from each of the lightSources in the scene. */
    unsigned int mPhotonsEmitted = 100000;

    /** Number of individual photons that will be searched as the nearest neighbours. */
    unsigned int mPhotonsNeighbours = 5000;

    /** Radius of the beam used in the radiance estimation. */
    float mBeamRadius = 0.01f;

    /** The scene's camera. */
    unique_ptr<Camera> mCamera;

    /** List of light Sources in the scene. */
    vector<shared_ptr<LightSource>> mLightSources;

    /** List of shapes in the scene. */
    vector<shared_ptr<Shape>> mShapes;

    /** List of participating media in the scene. */
    vector<shared_ptr<ParticipatingMedia>> mMedia;

    /** Main indirect light photon map. */
    KDTree mDiffusePhotonMap;

    /** Caustics exclusive photon map. */
    KDTree mCausticsPhotonMap;

    /** Participating media exclusive photon map. */
    KDTree mMediaPhotonMap;

    /**
     * @param horizontalLines Lines which pixels will be trace and saved to the image.
     * @param image Pointer to the image shared by all the threads rendering the scene and saving into it. No concurrency
     *  issues are expected because each thread renders separate lines.
     * @param printProgress If true, this thread will print a progress bar. Since the lines each thread renders are not
     *  contiguous we expect every thread to take a similar amount of time so it doesn't matter if the progress bar
     *  finishes before all other threads end. If all printed their own progress bar adding locks would make this slower.
     */
    void RenderPixelRange(const shared_ptr<vector<unsigned int>> horizontalLines,
                          const shared_ptr<Image> image, const bool printProgress) const;

    /**
     * Basic path tracing interaction between photons and the scene.
     *
     * @param lightRay Direction and position from which the photon is thrown, and color of this photon.
     * @param save true if the next intersection between the lightRay and a shape in the scene will be stored in a
     *  KDTree.
     */
    void PhotonInteraction(const ColoredLightRay &lightRay, const bool save);

    /**
     * Basic path tracing interaction between photons and the scene geometry.
     *
     * @param lightRay Direction and position from which the photon is thrown, and color of this photon.
     * @param shape Shape intersected by the lightRay, and with which the photon is interacting.
     * @param intersection Point where the lightRay intersects with the shape.
     * @param save true if intersection between the lightRay and the shape will be stored in a KDTree.
     */
    void GeometryInteraction(const ColoredLightRay &lightRay, const shared_ptr<Shape> &shape,
                             const Point &intersection, bool save);

    /**
     * Basic path tracing interaction between photons and the scene media.
     *
     * @param lightRay Direction and position from which the photon is thrown, and color of this photon.
     * @param media Media with which the photon is interacting.
     * @param interaction Point where the lightRay interacts with the media.
     * @param save true if interaction between the lightRay and the media will be stored in the media KDTree.
     */
    void MediaInteraction(const ColoredLightRay &lightRay, const shared_ptr<ParticipatingMedia> &media,
                          const Point &interaction, const bool save);

    /**
     * Path tracing for photons to store in the caustic map. If save is false and the first intersection has a non-refractive
     * or mirror surface the photon is dropped and the recursion ends.
     *
     * @param lightRay Direction and position from which the photon is thrown, and color of this photon.
     * @param save true if the next intersection between the lightRay and a shape in the scene should interact with non-refractive
     *  surfaces.
     */
    void CausticInteraction(const ColoredLightRay &lightRay, bool save);

    /**
     * Calculates the color of the first point that intersects the lightRay. If specularSteps is greater than 0 reflected
     * and refracted paths will be followed.
     *
     * @param lightRay LightRay to indicate where to look for intersections.
     * @param specularSteps Specular steps to take.
     * @return Color of the first intersection with the lightRay.
     */
    Color GetLightRayColor(const LightRay &lightRay, const int specularSteps) const;

    /**
     * @param point that belongs to the shape [shape] and where the direct light is calculated.
     * @param normal of the [shape]'s surface in the point [point] and seen from [seenFrom].
     * @param seenFrom Direction from which the point [point] is seen.
     * @param shape that defines the light distribution with its BRDF.
     * @return a color in relation to the direct light reached in the point [point] of the shape [shape] from
     *  all the light sources in the scene, and is distributed in the [seenFrom] * -1 direction.
     */
    Color DirectLight(const Point &point, const Vect &normal,
                      const LightRay &seenFrom, const Shape &shape) const;

    /**
     * @param point that belongs to the shape [shape] and where the specular light is calculated.
     * @param normal of the [shape]'s surface in the point [point].
     * @param in Incoming ray of light that intersects the shape [shape] in the point [point].
     * @param shape that defines the light distribution with its BRDF.
     * @param specularSteps Number of steps remaining to stop the specular bounces.
     * @return a color in relation to the specular light (reflection and refraction) reached in the point [point]
     *  of the shape [shape], performing [specularSteps] bounces of specular light.
     */
    Color SpecularLight(const Point &point, const Vect &normal,
                        const LightRay &in, const Shape &shape,
                        const int specularSteps) const;

    /**
     * @param point that belongs to the shape [shape] and where the diffuse light is estimated.
     * @param normal of the [shape]'s surface in the point [point].
     * @param in Incoming ray of light that intersects the shape [shape] in the point [point].
     * @param shape that defines the light distribution with its BRDF.
     * @return a color in relation to the estimated diffuse light reached in the point [point] of the shape [shape].
     */
    Color GeometryEstimateRadiance(const Point &point, const Vect &normal,
                                   const LightRay &in, const Shape &shape) const;

    /**
     * @param point where the ray of light will intersect the nearest shape of the scene.
     * @param in Ray of light whose radiance is being estimated in the media.
     * @return a color in relation to the estimated light of the ray of light [in] that pass through the media
     *  in the scene before intersecting with a shape in the point [point].
     */
    Color MediaEstimateRadiance(const Point &point, const LightRay &in) const;

    /**
     * It has the same goal than previous method, but avoiding the check of the calculation of the contribution of only
     * those photons that are closer than the intersection [point]. In this method, there is no intersection, and
     * all the photons are taking into account. Efficiency!
     *
     * @param in Ray of light whose radiance is being estimated in the media.
     * @return a color in relation to the estimated light of the ray of light [in] that pass through the media
     *  in the scene.
     */
    Color MediaEstimateRadiance(const LightRay &in) const;

    /**
     * @param point where the gaussian filter is applied.
     * @param photon Point of the photon.
     * @param radius Maximum radius, distance from point to the k nearest photon (radius of the gaussian).
     * @return a gaussian filter applied in the point [point] to the photon [photon].
     */
    float GaussianKernel(const Point &point, const Point &photon, const float radius) const;

    /**
     * @param lightRay to the light source [light] which is checked if any shape in the scene blocks the way to the light.
     * @param light source which is checked whether it's hidden or not from the ray of light [lightRay].
     * @return true if the light source [light] is hidden (in shadow) from the ray of light [lightRay], false otherwise.
     */
    bool InShadow(const LightRay &lightRay, const Point &light) const;
};

#endif // RAY_TRACER_SCENE_HPP
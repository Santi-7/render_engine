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
     * Sets this Scene's image width and height.
     *
     * @param width -
     * @param height -
     */
    void SetImageDimensions(unsigned int width, unsigned int height)
    {
        mCamera->SetImageDimensions(width, height);
    }

    /**
     * Sets the number of specular steps to take when rendering the image.
     *
     * @param steps
     */
    void SetSpecularSteps(unsigned int steps)
    {
        mSpecularSteps = steps;
    }

    /**
     * Sets the number of indirect steps to take when rendering the image.
     *
     * @param steps
     */
    void SetIndirectSteps(unsigned int steps)
    {
        mIndirectSteps = steps;
    }

    /**
     * Sets the number of indirect rays to trace when rendering the image.
     *
     * @param steps
     */
    void SetIndirectRays(unsigned int rays)
    {
        mIndirectRays = rays;
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

    // TODO: Check if this variable disappears.
    /** Limit to the diffuse interactions allowed. */
    unsigned int mIndirectSteps = 0;

    /** Number of individual photons that will be emitted from each of the lightSources in the scene. */
    unsigned int mPhotonsEmitted = 500000;

    // TODO: Check if a variable mNeighbourPhotons is smarter.

    /** The scene's camera. */
    unique_ptr<Camera> mCamera;

    /** List of light Sources in the scene. */
    vector<shared_ptr<LightSource>> mLightSources;

    /** List of shapes in the scene. */
    vector<shared_ptr<Shape>> mShapes;

    /** Main indirect light photon map. */
    KDTree mPhotonMap;

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
     *      KDTree.
     */
    void PhotonInteraction(const ColoredLightRay &lightRay, bool save);

    /**
     * Calculates the color of the first point that intersects the lightRay. If specularSteps is greater than 0 reflected
     * and refracted paths will be followed. If diffuseSteps is greater than 0 a diffuse sampling will be taken into account
     * for the final color returned.
     *
     * @param lightRay LightRay to indicate where to look for intersections.
     * @param specularSteps Specular steps to take.
     * @param diffuseSteps Diffuse steps to take.
     * @return Color of the first intersection with the lightRay.
     */
    Color GetLightRayColor(const LightRay &lightRay,
                           const int specularSteps,
                           const int diffuseSteps) const;

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
     * @param diffuseSteps Number of steps remaining to stop the diffuse bounces.
     * @return a color in relation to the specular light (reflection and refraction) reached in the point [point]
     *  of the shape [shape], performing [specularSteps] bounces of specular light.
     */
    Color SpecularLight(const Point &point, const Vect &normal,
                        const LightRay &in, const Shape &shape,
                        const int specularSteps, const int diffuseSteps) const;

    /**
     * TODO: Add doc if necessary: the meaning has been change from diffuse light to estimated radiance.
     * @param point that belongs to the shape [shape] and where the diffuse light is calculated.
     * @param normal of the [shape]'s surface in the point [point].
     * @param in Incoming ray of light that intersects the shape [shape] in the point [point].
     * @param shape that defines the light distribution with its BRDF.
     * @param diffuseSteps Number of steps remaining to stop the diffuse bounces.
     * @return a color in relation to the diffuse light reached in the point [point]
     *  of the shape [shape], performing [diffuseSteps] bounces of diffuse light.
     */
    Color EstimateRadiance(const Point &point, const Vect &normal,
                           const LightRay &in, const Shape &shape,
                           const int diffuseSteps) const;

    /**
     * @param lightRay to the light source [light] which is checked if any shape in the scene blocks the way to the light.
     * @param light source which is checked whether it's hidden or not from the ray of light [lightRay].
     * @return true if the light source [light] is hidden (in shadow) from the ray of light [lightRay], false otherwise.
     */
    bool InShadow(const LightRay &lightRay, const Point &light) const;
};

#endif // RAY_TRACER_SCENE_HPP
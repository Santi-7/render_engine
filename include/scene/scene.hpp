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

private:

    /** Limit to the specular interactions allowed. */
    unsigned int mSpecularSteps = 4;

    /** Limit to the diffuse interactions allowed. */
    unsigned int mIndirectSteps = 0;

    /** Diffuse rays to throw in every diffuse interaction. */
    unsigned int mIndirectRays = 8;

    /** The scene's camera. */
    unique_ptr<Camera> mCamera;

    /** List of light Sources in the scene. */
    vector<shared_ptr<LightSource>> mLightSources;

    /** List of shapes in the scene. */
    vector<shared_ptr<Shape>> mShapes;

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
     * .
     *
     * @param point .
     * @param normal .
     * @param seenFrom .
     * @param shape .
     * @return .
     */
    Color DirectLight(const Point &point, const Vect &normal,
                      const LightRay &seenFrom, const Shape &shape) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param normal .
     * @param in .
     * @param shape .
     * @param specularSteps .
     * @param diffuseSteps .
     * @return .
     */
    Color SpecularLight(const Point &point, const Vect &normal,
                        const LightRay &in, const Shape &shape,
                        const int specularSteps, const int diffuseSteps) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param normal .
     * @param in.
     * @param shape .
     * @param specularSteps .
     * @param diffuseSteps .
     * @return .
     */
    Color DiffuseLight(const Point &point, const Vect &normal,
                       const LightRay &in, const Shape &shape,
                       const int specularSteps, const int diffuseSteps) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @param light .
     * @return .
     */
    bool InShadow(const LightRay &lightRay, const Point &light) const;
};

#endif // RAY_TRACER_SCENE_HPP
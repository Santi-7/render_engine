/* ---------------------------------------------------------------------------
** scene.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include <camera.hpp>
#include <lightSource.hpp>
#include <shape.hpp>
#include <vector>

using namespace std;

class Scene {

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param c .
     */
    void SetCamera(const Camera &camera);

    // TODO: Add doc.
    /**
     * .
     *
     * @param number .
     */
    void SetNumberOfLightSources(const unsigned int number);

    // TODO: Add doc.
    /**
     * .
     *
     * @param s .
     */
    void AddLightSource(const LightSource &lightSource);

    // TODO: Add doc.
    /**
     * .
     *
     * @param number .
     */
    void SetNumberOfShapes(const unsigned int number);

    // TODO: Add doc.
    /**
     * .
     *
     * @param s .
     */
    void AddShape(const Shape &shape);

private:

    // TODO: Add doc.
    /* . */
    Camera mCamera;

    // TODO: Add doc.
    /* . */
    vector<LightSource> mLightSources;

    // TODO: Add doc.
    /* . */
    vector<Shape> mShapes;
};

#endif // RAY_TRACER_SCENE_HPP
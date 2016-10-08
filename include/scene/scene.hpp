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
     * @param camera .
     */
    void SetCamera(const Camera &camera);

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightSource .
     */
    void AddLightSource(const LightSource &lightSource);

    // TODO: Add doc.
    /**
     * .
     *
     * @param shape .
     */
    void AddShape(const Shape &shape);

    // TODO: Add doc.
    /**
     *
     */
    void Render() const;

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
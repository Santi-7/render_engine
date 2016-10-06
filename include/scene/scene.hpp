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
    void SetCamera(const Camera &c);

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
    void AddShape(const Shape &s);

private:

    Camera mCamera;

    // TODO: Add doc.
    /* . */
    vector<Shape> mShapes;
};

#endif // RAY_TRACER_SCENE_HPP
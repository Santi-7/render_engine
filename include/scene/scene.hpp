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
#include <memory>
#include <shape.hpp>
#include <vector>

using namespace std;

class Scene {

public:

    template <class C>
    void SetCamera(const C &camera)
    {
        mCamera = make_unique<C>(camera);
    }

    template <class LS>
    void AddLightSource(const LS &lightSource)
    {
        mLightSources.push_back(make_unique<LS>(lightSource));
    }

    template <class S>
    void AddShape(const S &shape)
    {
        mShapes.push_back(make_unique<S>(shape));
    }

    // TODO: Add doc.
    /**
     *
     */
    void Render() const;

private:

    // TODO: Add doc.
    /* . */
    unique_ptr<Camera> mCamera;

    // TODO: Add doc.
    /* . */
    vector<unique_ptr<LightSource> > mLightSources;

    // TODO: Add doc.
    /* . */
    vector<unique_ptr<Shape> > mShapes;

    // TODO: Add doc.
    /**
     * .
     *
     * @param pixel .
     * @return .
     */
    Color GetPixelColor(const Point &pixel) const;
};

#endif // RAY_TRACER_SCENE_HPP
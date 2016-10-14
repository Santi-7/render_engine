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
        mLightSources.push_back(make_shared<LS>(lightSource));
    }

    template <class S>
    void AddShape(const S &shape)
    {
        mShapes.push_back(make_shared<S>(shape));
    }

    // TODO: Add doc.
    /**
     *
     */
    unique_ptr<Image> Render() const;

private:

    // TODO: Add doc.
    /* */
    static constexpr unsigned int REFLECT_STEPS = 2;

    // TODO: Add doc.
    /* . */
    unique_ptr<Camera> mCamera;

    // TODO: Add doc.
    /* . */
    vector<shared_ptr<LightSource>> mLightSources;

    // TODO: Add doc.
    /* . */
    vector<shared_ptr<Shape>> mShapes;

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @param reflectedSteps .
     * @return .
     */
    Color GetLightRayColor(const LightRay &lightRay,
                           unsigned int reflectedSteps) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @param normal .
     * @return .
     */
    Color DirectLight(const Point &point, const Vect &normal) const;

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
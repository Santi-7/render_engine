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
#include <image.hpp>
#include <mutex>

using namespace std;

class PixelGetter{
public:

    PixelGetter() : mCurrentPixel(Point(0,0,0)), mxIncrement(Vect(1,0,0)), myIncrement(Vect(0,1,0)), mLock() {}

    PixelGetter(Point beginning, Vect xIncrement, Vect yIncrement, unsigned int width, unsigned int height)
            : mCurrentPixel(beginning), mxIncrement(xIncrement), myIncrement(yIncrement),
              mWidth(width), mHeight(height), mX(0), mY(0), mLock(){}

    unique_ptr<tuple<Point, unsigned int, unsigned int>> GetNextPixel() {
        lock_guard<mutex> lock{mLock};
        if(mY > mHeight-1) return nullptr;

        auto retVal = make_unique<tuple<Point, unsigned int, unsigned int>>(mCurrentPixel, mX, mY);
        if(mX == mWidth)
        {
            mX = 0; mY++;
            mCurrentPixel += myIncrement;
            mCurrentPixel -= mxIncrement * mWidth;
        }
        else
        {
            mX++;
            mCurrentPixel += mxIncrement;
        }
        return retVal;
    }

private:
    Point mCurrentPixel;
    Vect mxIncrement, myIncrement;
    unsigned int mWidth, mHeight, mX, mY;
    mutable mutex mLock;
};

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
/* ---------------------------------------------------------------------------
** box.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_BOX_HPP
#define RAY_TRACER_BOX_HPP

#include <rectangle.hpp>

class Box : public Shape
{

public:

    // TODO: Add doc.
    /**
     * Constructs a Box.
     *
     * @param base .
     * @param depth .
     * @return .
     */
    Box(const Rectangle &base, const float depth);

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @return .
     */
    float Intersect(const LightRay &lightRay) const;

    // TODO: Add doc.
    /**
     * .
     * @param lightRay
     * @param minT
     * @param nearestShape
     * @param thisShape
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const;

    /**
     * This method is not usable for this shape.
     * If called, a static error should pop up.
     */
    Vect GetNormal(const Point &point) const;

    void SetMaterial(shared_ptr<Material> material);

    template <class M>
    void SetMaterial(M material)
    {
        for (const shared_ptr<Rectangle> &face : mFaces)
        {
            face->SetMaterial(material);
        }
    }

protected:

    // TODO: Add doc.
    /* . */
    array<shared_ptr<Rectangle>, 6> mFaces; // A box has 6 faces.
};

#endif //RAY_TRACER_BOX_HPP
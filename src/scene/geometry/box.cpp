/* ---------------------------------------------------------------------------
** box.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <box.hpp>
#include <cfloat>

Box::Box(const FinitePlane &base, const float depth)
: Shape()
{
    /* Base face. */
    mFaces[0] = make_shared<FinitePlane>(base);
    /* Top face. */
    Point cornerA, cornerB;
    tie(cornerA, cornerB) = base.GetLimits();
    // The top face is the base face moved [depth] along its normal.
    Point cornerATop = cornerA + base.GetNormal() * depth;
    Point cornerBTop = cornerB + base.GetNormal() * depth;
    mFaces[1] = make_shared<FinitePlane>(FinitePlane(base.GetNormal(), cornerATop, cornerBTop));
    /* Lateral faces. */
    Vect lateralNormal1 = (cornerA - cornerB).CrossProduct(base.GetNormal()).Normalise();
    mFaces[2] = make_shared<FinitePlane>(FinitePlane(lateralNormal1, cornerA, cornerATop));
    mFaces[3] = make_shared<FinitePlane>(FinitePlane(lateralNormal1, cornerB, cornerBTop));
    // Normalisation don't needed because lateralNormal1 and GetNormal are already normalised.
    Vect lateralNormal2 = lateralNormal1.CrossProduct(base.GetNormal());
    mFaces[4] = make_shared<FinitePlane>(FinitePlane(lateralNormal2, cornerA, cornerATop));
    mFaces[5] = make_shared<FinitePlane>(FinitePlane(lateralNormal2, cornerB, cornerBTop));
}

float Box::Intersect(const LightRay &lightRay) const
{
    // Check if the ray of light intersects with any of the box's face.
    for (const shared_ptr<FinitePlane> &face : mFaces)
    {
        float t = face->Intersect(lightRay);
        // The ray of light intersects with the current face.
        if (t < FLT_MAX) return t;
    }
    // The ray of light hasn't intersected with any of the box's faces.
    return FLT_MAX;
}

Vect Box::GetVisibleNormal(const Point &point, const LightRay &seenFrom) const
{
    static_assert(true, "This method should not be called, call the method on an individual finite plane.\n");
}
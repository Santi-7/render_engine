/* ---------------------------------------------------------------------------
** box.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <box.hpp>
#include <cfloat>
#include <iostream>

Box::Box(const Rectangle &base, const float depth)
: Shape()
{
    /* Base face. */
    mFaces[0] = make_shared<Rectangle>(base);
    /* Top face. */
    Point cornerA1, cornerA2, cornerB1, cornerB2;
    tie(cornerA1, cornerA2, cornerB1, cornerB2) = base.GetLimits();
    // The top face is the base face moved [depth] along its normal.
    Point cornerATop = cornerA1 + base.GetNormal() * depth;
    Point cornerBTop = cornerB1 + base.GetNormal() * depth;
    mFaces[1] = make_shared<Rectangle>(Rectangle(base.GetNormal(), cornerATop, cornerBTop));
    /* Lateral faces. */
    Vect up = (cornerA1 - cornerA2).Normalise();
    Vect right = (cornerB2 - cornerA1).Normalise();
    cout << endl;
    cout << cornerA1 << " " << cornerB2 << endl;
    cout << cornerA2 << " " << cornerB1 << endl;
    cout << "UP" << up << endl;
    cout << "RIGHT" << right << endl;
    mFaces[2] = make_shared<Rectangle>(Rectangle(up, cornerB2, cornerATop));
    mFaces[3] = make_shared<Rectangle>(Rectangle(up, cornerA2, cornerBTop));
    mFaces[4] = make_shared<Rectangle>(Rectangle(right, cornerA2, cornerATop));
    mFaces[5] = make_shared<Rectangle>(Rectangle(right, cornerB2, cornerBTop));
}

float Box::Intersect(const LightRay &lightRay) const
{
    float tMin = FLT_MAX;
    // Check if the ray of light intersects with any of the box's face.
    for (const shared_ptr<Rectangle> &face : mFaces)
    {
        float t = face->Intersect(lightRay);
        if (t < tMin) tMin = t;
    }
    // The ray of light intersects with the current face.
    return tMin;
}

void Box::Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                    shared_ptr<Shape> thisShape) const {
    // Check if the ray of light intersects with any of the box's face.
    for (const shared_ptr<Rectangle> &face : mFaces)
    {
        face->Intersect(lightRay, minT, nearestShape, face);
    }
}

Vect Box::GetVisibleNormal(const Point &point, const LightRay &seenFrom) const
{
    throw 1;
}
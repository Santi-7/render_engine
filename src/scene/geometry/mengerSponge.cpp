/** ---------------------------------------------------------------------------
 ** mergerSponge.cpp
 ** MergerSponge implementation.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <geometry/mengerSponge.hpp>
#include <cfloat>

MengerSponge::MengerSponge(float distanceToEdgeFromOrigin, int recursion, shared_ptr<Material> material, Vect originShift)
        :mBox(
        Rectangle(
                Vect(0, 1, 0),
                Point(-distanceToEdgeFromOrigin, -distanceToEdgeFromOrigin, -distanceToEdgeFromOrigin) + originShift,
                Point(distanceToEdgeFromOrigin, -distanceToEdgeFromOrigin, distanceToEdgeFromOrigin) + originShift),
        2 * distanceToEdgeFromOrigin)
{
    // With recursion 5 this takes up to 6-7GB of memory. With 6 it could crash most computers.
    if (recursion > 5) recursion = 5;
    if (recursion == 0)
    {
        mIsACube = true;
        mBox.SetMaterial(material);
        // Set all sub-sponge pointers to null.
        for (unsigned int i = 0; i < mSubSponges.size(); ++i)
        {
            mSubSponges[i] = nullptr;
        }
    }
    else
    {
        recursion--;
        // Initialize the sub-sponges
        float newCubeShift = distanceToEdgeFromOrigin * 2.0f / 3.0f;
        unsigned char cubeIdCounter = 0;
        Vect newCubeOriginShift;
        for (int x = -1; x < 2; ++x)
        {
            for (int y = -1; y < 2; ++y)
            {
                for (int z = -1; z < 2; ++z)
                {
                    if (((x == 0) & (y == 0)) || ((x == 0) & (z == 0)) || ((y == 0) & (z == 0))) continue;
                    float shiftX = newCubeShift * x, shiftY = newCubeShift * -y, shiftZ = newCubeShift * z;

                    newCubeOriginShift = Vect(originShift.GetX() + shiftX, originShift.GetY() + shiftY, originShift.GetZ() + shiftZ);
                    mSubSponges[cubeIdCounter++] = make_shared<MengerSponge>(newCubeShift/2, recursion, material, newCubeOriginShift);
                }
            }
        }
    }
}

float MengerSponge::Intersect(const LightRay& lightRay) const
{
    if (mIsACube) return mBox.Intersect(lightRay);

    if (mBox.Intersect(lightRay) != FLT_MAX)
    {
        for (const shared_ptr<MengerSponge> &subSponge : mSubSponges)
        {
            float tmp = subSponge->Intersect(lightRay);
            if (tmp != FLT_MAX) return tmp;
        }
    }

    return FLT_MAX;
}

void MengerSponge::Intersect(const LightRay& lightRay, float& minT, shared_ptr<Shape>& nearestShape,
        shared_ptr<Shape> thisShape) const
{
    if (mIsACube) mBox.Intersect(lightRay, minT, nearestShape, thisShape);
    else
    {
        if (mBox.Intersect(lightRay) != FLT_MAX)
        {
            array<tuple<float, unsigned int>, 20> boundIntersections;

            for (unsigned int i = 0; i < mSubSponges.size(); ++i)
            {
                boundIntersections[i] = make_tuple(mSubSponges[i]->mBox.Intersect(lightRay), i);
            }
            sort(boundIntersections.begin(), boundIntersections.end(),
                    [](tuple<float, unsigned int> const& t1, tuple<float, unsigned int> const& t2)
                    {
                        return get<0>(t1)<get<0>(t2);
                    });
            float tmpT;
            // A lightRay can never intersect a menger sponge in more than four sub-cubes
            for (unsigned int i = 0; i < 4; ++i)
            {
                tmpT = minT;
                int index = get<1>(boundIntersections[i]);
                mSubSponges[index]->Intersect(lightRay, minT, nearestShape, mSubSponges[index]);
                if (minT != tmpT) break; // No intersection can be at a smaller t than this one
            }
        }
    }
}

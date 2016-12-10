/** ---------------------------------------------------------------------------
 ** mergerSponge.hpp
 ** A recursively generated shape made out of cubes.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MERGERSPONGE_HPP
#define RAY_TRACER_MERGERSPONGE_HPP

#include <vector>
#include "shape.hpp"
#include "box.hpp"

class MengerSponge : public Shape{
public:

    /**
     * Constructs a new MergerSponge with the given recursion (amount of detail).
     * @param distanceToEdgeFromOrigin Distance from the origin to any of the edges of the biggest cube.
     * @param recursion Steps left. If 0 this MergerSponge will be just a Box.
     */
    MengerSponge(float distanceToEdgeFromOrigin, int recursion, shared_ptr<Material> material = LAMBERTIAN, Vect originShift = Vect(0,0,0));

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to any of this box's faces. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    float Intersect(const LightRay &lightRay) const;

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @param minT Minimum distance from the lightRay's origin to any shape so far. If this shape is closer to the origin
     *  than this value then it will be updated to that distance.
     * @param nearestShape Shape that is reportedly the closest to the lightRay's origin so far. If any of the rectangles
     * in this box is closer then it will be updated to that rectangle's pointer.
     * @param thisShape Unused.
     */
    void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape, shared_ptr<Shape> thisShape) const;

    /**
     * This method is not usable for this shape since it makes no sense for it to have a normal.
     */
    Vect GetNormal(const Point &point) const {throw 1;}

private:
    /** True if this sponge is just a cube*/
    bool mIsACube = false;

    /** Container for the sub sponges in this sponge*/
    array<shared_ptr<MengerSponge>, 20> mSubSponges;
    Box mBox;
};

#endif //RAY_TRACER_MERGERSPONGE_HPP

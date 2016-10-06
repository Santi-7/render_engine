/* ---------------------------------------------------------------------------
** intersections.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <intersections.hpp>

Point GetIntersection(const LightRay &lightRay, const float t) const
{
    // Return the intersection point if it is in front of the camera.
    return t > threshold ? lightRay.GetPoint(t) : NULL;
}

Point GetIntersection(const LightRay &lightRay, const float t_1, const float t_2) const
{
    /*
     * Intersection Point 1 is in front of the camera and
     * (before Point 2 or it is the only in front of the camera).
     */
    if ((t_1 < t_2 | t_2 <= threshold) & (t_1 > threshold))
    {
        return lightRay.GetPoint(t_1);
    }
    /*
     * Intersection Point 2 is in front of the camera and
     * (before Point 1 or it is the only in front of the camera).
     */
    else if ((t_2 < t_1 | t_1 <= threshold) & (t_2 > threshold))
    {
        return lightRay.GetPoint(t_2);
    }
    // Both intersection points are behind the camera.
    else // t_1 <= threshold & t_2 <= threshold.
    {
        return NULL;
    }
}
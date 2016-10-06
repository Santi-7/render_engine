/* ---------------------------------------------------------------------------
** sphere.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <cmath>
#include <sphere.hpp>

Sphere::Sphere(const Point &center, const float radius)
: Shape(), mCenter(center), mRadius(radius)
{}

Point Sphere::intersect(const LightRay &lightRay) const
{
    float a = lightRay.GetDirection().DotProduct(lightRay.GetDirection());
    // Shorted to gain efficiency.
    float b = 2 * lightRay.GetDirection().DotProduct(lightRay.GetSource() - mCenter);
    float c = lightRay.GetSource() * lightRay.GetSource() +
              mCenter * mCenter -
              2 * (lightRay.GetSource() * mCenter) -
              mRadius * mRadius;
    float bb_4ac = b*b - 4*a*c;
    // Ordered by probability of occurrence.
    /* The ray of light doesn't intersect with the sphere. */
    if (bb_4ac < 0)
    {
        return NULL;
    }
    /* The ray of light intersects with the sphere. */
    else if (bb_4ac > 0)
    {
        float t_1 = (float) (-b - sqrt(bb_4ac)) / (2 * a);
        float t_2 = (float) (-b + sqrt(bb_4ac)) / (2 * a);
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
    /* The ray of light is a tangent line of the sphere. */
    else // (b*b - 4*a*c = 0)
    {
        float t = -b / (2 * a);
        /*
         * Return the point where the ray of light intersects
         * with the sphere if it is in front of the camera.
         */
        return t > threshold ? lightRay.GetPoint(t) : NULL;
    }
}

const float Sphere::threshold = 0.001;
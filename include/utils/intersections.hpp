/* ---------------------------------------------------------------------------
** intersections.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_INTERSECTIONS_HPP
#define RAY_TRACER_INTERSECTIONS_HPP

#include <lightRay.hpp>

// TODO: Add doc.
/* . */
static const float threshold = 0.001;

// TODO: Add doc.
/**
 * .
 *
 * @param lightRay .
 * @param t .
 * @return .
 */
Point GetIntersection(const LightRay &lightRay, const float t) const;

// TODO: Add doc.
/**
 * .
 *
 * @param lightRay .
 * @param t_1 .
 * @param t_2 .
 * @return .
 */
Point GetIntersection(const LightRay &lightRay, const float t_1, const float t_2) const;

#endif // RAY_TRACER_INTERSECTIONS_HPP
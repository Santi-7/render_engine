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
static constexpr float threshold = 0.001;

// TODO: Add doc.
/**
 * .
 *
 * @param t .
 * @return .
 */
float GetNearestInFront(const float t);

// TODO: Add doc.
/**
 * .
 *
 * @param t_1 .
 * @param t_2 .
 * @return .
 */
float GetNearestInFront(const float t_1, const float t_2);

#endif // RAY_TRACER_INTERSECTIONS_HPP
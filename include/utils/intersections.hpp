/* ---------------------------------------------------------------------------
** intersections.hpp
** THis class manages if an intersection point between a ray of light and a shape is
** in the direction of the ray, this is, the shape is visible.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_INTERSECTIONS_HPP
#define RAY_TRACER_INTERSECTIONS_HPP

#include <lightRay.hpp>

/* In order that a shape doesn't intersect with itself, this threshold is required. */
static constexpr float threshold = 0.001;

/**
 * Returns [t] if it's positive (in front) and greather than threshold. This means
 * that a ray of light has intersected a visible shape (in the ray of light direction)
 * and this shape isn't in the source of the ray of light. Otherwhise, FLT_MAX is returned.
 *
 * @param t Value to check if it's in front.
 * @return [t] if it's positive and greather than threshold, FLT_MAX otherwise.
 */
float GetNearestInFront(const float t);

/**
 * Returns the minimum value between [t_1] and [t_2] (the nearest) on the condition that
 * they are positive and greater (in front) than threshold. This means that a ray of light
 * has intersected a visible shape (in the ray of light direction) and this shape isn't
 * in the source of the ray of light. Otherwhise, FLT_MAX is returned.
 *
 * @param t_1 First value to check if it's the nearest and in front.
 * @param t_2 Second value to check if it's the nearest and in front.
 * @return The minimum value between [t_1] and [t_2], on the condition that they
 * are positive and greater than threshold, FLT_MAX otherwise.
 */
float GetNearestInFront(const float t_1, const float t_2);

#endif // RAY_TRACER_INTERSECTIONS_HPP
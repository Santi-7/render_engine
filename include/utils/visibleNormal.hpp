/* ---------------------------------------------------------------------------
** visibleNormal.hpp
** This class manages which is the normal vector of a shape at a point
 * that is seen (visible) from certain direction.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_VISIBLE_NORMAL_HPP
#define RAY_TRACER_VISIBLE_NORMAL_HPP

#include <vect.hpp>

/**
 * Returns the [normal] vector that points to [seenFrom], this is, the direction
 * of [normal] that forms more than 90º with [seenFrom].
 *
 * @param normal Vector to return its direction.
 * @param seenFrom Vector which the normal must point to.
 * @return the direction of [normal] that forms more than 90º with [seenFrom].
 */
Vect VisibleNormal(const Vect &normal, const Vect &seenFrom);

#endif // RAY_TRACER_VISIBLE_NORMAL_HPP
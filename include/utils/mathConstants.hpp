/* ---------------------------------------------------------------------------
** mathConstants.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATH_CONSTANTS_H
#define RAY_TRACER_MATH_CONSTANTS_H

typedef float refractiveIndex;

static constexpr float PI = 3.1415926535897932f;

// TODO: Add doc.
/* . */
static constexpr refractiveIndex VACUUM_RI  = 1.0f;
static constexpr refractiveIndex AIR_RI     = 1.0002926f;
static constexpr refractiveIndex WATER_RI   = 1.333f;
static constexpr refractiveIndex QUARTZ_RI  = 1.544f;
static constexpr refractiveIndex GLASS_RI   = 1.52f;
static constexpr refractiveIndex DIAMOND_RI = 2.42f;

#endif // RAY_TRACER_MATH_CONSTANTS_H
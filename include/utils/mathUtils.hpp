/** ---------------------------------------------------------------------------
 ** mathUtils.hpp
 ** Contains math and physics constants and utils.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATH_CONSTANTS_H
#define RAY_TRACER_MATH_CONSTANTS_H

#include <random>
#include <tuple>

using namespace std;

typedef float refractiveIndex;

/** PI const value. */
static constexpr float PI = 3.1415926535897932f;

/** Some refractive indices definitions to make life easier when making simple scenes. */
static constexpr refractiveIndex VACUUM_RI  = 1.0f;
static constexpr refractiveIndex AIR_RI     = 1.0002926f;
static constexpr refractiveIndex WATER_RI   = 1.333f;
static constexpr refractiveIndex QUARTZ_RI  = 1.544f;
static constexpr refractiveIndex GLASS_RI   = 1.52f;
static constexpr refractiveIndex DIAMOND_RI = 2.42f;

/**
 * @return Random value between 0 and 1.
 */
inline static float GetRandomValue()
{
    // Random generator.
    static random_device randDev;
    static mt19937 mt(randDev());
    static uniform_real_distribution<float> distribution(0, 1);
    return distribution(mt);
}

/**
 * @return Tuple with a randomly selected inclination and azimuth the inclination being biased towards higher angles.
 * Meant to sample a semi-sphere with higher chances of getting a sample that goes straight up from its base.
 */
inline static tuple<float, float> UniformCosineSampling()
{
    // Inclination and azimuth angles.
    float inclination = acos(sqrt(1 - GetRandomValue()));
    float azimuth = 2 * PI * GetRandomValue();
    return make_tuple(inclination, azimuth);
}

/**
 * @return Tuple with a randomly selected inclination and azimuth. Meant to sample a sphere uniformly.
 */
inline static tuple<float, float> UniformSphereSampling()
{
    // Inclination and azimuth angles.
    float inclination = acos(2 * GetRandomValue() - 1);
    float azimuth = 2 * PI * GetRandomValue();
    return make_tuple(inclination, azimuth);
}

/**
 * @return Tuple with a randomly selected inclination and azimuth. Meant to sample a Phong specular lobe.
 */
inline static tuple<float, float> PhongSpecularLobeSampling(const float alpha)
{
    // Inclination and azimuth angles.
    float inclination = acos(pow(GetRandomValue(), 1 / (alpha + 1)));
    float azimuth = 2 * PI * GetRandomValue();
    return make_tuple(inclination, azimuth);
}

#endif // RAY_TRACER_MATH_CONSTANTS_H